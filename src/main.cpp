#include <algorithm>
#include <functional>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <array>

#include "Definitions.hpp"

#include "Gla/Gla.hpp"
#include "glm/glm.hpp"

#include "Chunk.hpp"
#include "Player.hpp"

using namespace std::chrono_literals;

constexpr float WINDOW_TITLE_UPDATE_TIME = 0.7f;

GLenum draw_mode = GL_TRIANGLES;

struct Point {
    float x;
    float y;
    float z;
};

struct ChunkCoords {
    int x, z;
};

void HandleEvents(GLFWwindow* window)
{
    glfwPollEvents();
    player.HandleEvents(window);

    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT))
    {
        static Gla::Timer time_after_pushing;

        if (time_after_pushing.GetTime() > 0.2f /*seconds*/)
        {
            if (draw_mode == GL_TRIANGLES)
                draw_mode = GL_LINES;
            else
                draw_mode = GL_TRIANGLES;

            time_after_pushing.Reset();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

int main(int argc, char *argv[])
{
    #ifdef GLA_DEBUG
        std::cout << "\n~In debug mode~\n";
        std::cout << "C++" << __cplusplus << '\n';
    #endif

    /* Initialize the library */
    if (!glfwInit()) {
        return 1;
    }

    glfwSetErrorCallback(&glfwError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create window.\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    else
    {
        std::cout << "GLFW raw mouse motion not suppported\n";
    }

    glfwSetCursorPosCallback(window, Player::CursorPosCallback);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew init error\n";
    }

    std::cout << glGetString(GL_VERSION) << '\n';

    GLCall( glEnable(GL_DEPTH_TEST) );
    GLCall( glDepthFunc(GL_GREATER) );

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {  // Without this block, OpenGL vars would go out of scope after calling glfwTerminate, which would freeze the program
    // glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, -8.0f, 8.0f) * glm::perspective<float>(glm::radians(10.0f), 1280.0f / 960.0f, 0.1f, 1.0f);
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(player.x_pos, player.y_pos, player.z_pos));

    const Gla::Texture2D grass_texture("assets/grass.png");
    const Gla::Texture2D grassnd_texture("assets/grassnd.png");
    const Gla::Texture2D dirt_texture("assets/dirt.png");
    const Gla::Texture2D log_texture("assets/log_side.png");
    const Gla::Texture2D stone_texture("assets/stone.png");
    const Gla::Texture2D sand_texture("assets/sand.png");
    const Gla::Texture2D leaves_texture("assets/leaves.png", Gla::GLMinMagFilter::NEAREST);
    const Gla::Texture2D water_texture("assets/water.png", Gla::GLMinMagFilter::NEAREST);

    GLint dims[2];
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &dims[0]);

    Gla::FrameBuffer shadowmap_framebuffer(dims[0], dims[1]);
    Gla::FrameBuffer::BindToDefaultFB(WINDOW_WIDTH, WINDOW_HEIGHT);

    enum TextureBinding { NON_TRANSPARENT, TRANSPARENT };
    std::function<void(TextureBinding)> bind_textures = [&](TextureBinding binding)
    {
        switch (binding) 
        {
        case NON_TRANSPARENT:
            GLCall( glBindTextureUnit(0, grass_texture.GetID())     );
            GLCall( glBindTextureUnit(1, dirt_texture.GetID())      );
            GLCall( glBindTextureUnit(2, grassnd_texture.GetID())   );
            GLCall( glBindTextureUnit(3, log_texture.GetID())       );
            GLCall( glBindTextureUnit(4, stone_texture.GetID())     );
            GLCall( glBindTextureUnit(5, sand_texture.GetID())      );
            GLCall( glBindTextureUnit(6, shadowmap_framebuffer.GetTextureID()) );
            break;
        case TRANSPARENT:
            GLCall( glBindTextureUnit(0, leaves_texture.GetID()) );
            GLCall( glBindTextureUnit(1, water_texture.GetID())  );
            break;
        default:
            LOG("Wrong 'TextureBinding' value in bind_textures lambda. From line: " << __LINE__);
        }
    };

    Gla::Renderer renderer;
    Gla::VertexBufferLayout* layout = new Gla::VertexBufferLayout;

    float sky_vertices[] = {
       -1.0f,  1.0f,
       -1.0f, -1.0f,
        1.0f, -1.0f,

       -1.0f,  1.0f,
        1.0f,  1.0f,
        1.0f, -1.0f,
    };

    Gla::VertexArray sky_va;
    Gla::VertexBuffer sky_vb(sky_vertices, sizeof(sky_vertices));
    layout->Push<float>(2);
    sky_va.AddBuffer(sky_vb, *layout);
    delete layout;
    Gla::Shader sky_shader("shader/SkyShader.glsl");

    Gla::Mesh sky_mesh(sky_va, sky_shader);

    // float hud_vertices[] = {
    //     -0.7f,  0.3f,
    //     -0.7f, -0.3f,
    //      0.7f,  0.3f,

    //      0.7f,  0.3f,
    //     -0.7f, -0.3f,
    //      0.7f, -0.3f,
         
    //      0.3f, -0.7f,
    //     -0.3f, -0.7f,
    //      0.3f,  0.7f,

    //      0.3f,  0.7f,
    //     -0.3f, -0.7f,
    //     -0.3f,  0.7f,
    // };

    // VertexArray hud_va;
    // VertexBuffer hud_vb(hud_vertices, sizeof(hud_vertices));
    // layout = new VertexBufferLayout;
    // layout->Push<float>(2);
    // hud_va.AddBuffer(hud_vb, *layout);
    // delete layout;
    // Shader hud_shader("shader/HudVertShader.vert", "sahder/HudFragShader.frag");

    // Mesh hud_mesh(hud_va, hud_shader);

    Gla::VertexArray transparent_va;
    Gla::VertexBuffer transparent_vb(nullptr, 0);
    layout = new Gla::VertexBufferLayout;
    layout->Push<float>(3);
    layout->Push<float>(2);
    layout->Push<float>(1);
    transparent_va.AddBuffer(transparent_vb, *layout);  // The same layout is needed
    Gla::Shader transparent_shader("shader/TranVertShader.vert", "shader/TranFragShader.frag");

    Gla::Mesh transparent_mesh(transparent_va, transparent_shader);

    transparent_mesh.Bind();
    int transparent_sampler_data[] = { 0, 1 };
    transparent_shader.SetUniform1iv("u_Samplers", 2, transparent_sampler_data);

    Gla::VertexArray world_va;
    Gla::VertexBuffer world_vb(nullptr, 0);
    world_va.AddBuffer(world_vb, *layout);
    delete layout;
    Gla::Shader world_shader("shader/VertShader.vert", "shader/FragShader.frag");
    Gla::Shader shadow_shader("shader/ShadowVertShader.vert", "shader/ShadowFragShader.frag");

    Gla::Mesh world_mesh(world_va, world_shader);
    Gla::Mesh shadow_mesh_nontransparent(world_va, shadow_shader);
    Gla::Mesh shadow_mesh_transparent(transparent_va, shadow_shader);

    world_shader.Bind();
    int sampler_data[] = { 0, 1, 2, 3, 4, 5, 6 };
    world_shader.SetUniform1iv("u_Samplers", 7, sampler_data);

    Gla::UniformBuffer ubo(0, &PROJECTION_MTR[0][0]);  // This is used in the 'Player' class to update the view projection matrix
    // Gla::UniformBuffer ubo_sun(1, &PROJECTION_MTR[0][0]);  // This is used in the 'Player' class to update the view projection matrix
    ubo.Bind();
    // ubo_sun.Bind();

    player.SetUniformBuffer(ubo);

    Gla::Timer out_of_loop_timer;
    // player.GravityOff();

    ChunkCoords last_frame_chunkcoords = { player.ChunkX(), player.ChunkZ() };

    /* Game loop */
    while (!glfwWindowShouldClose(window))
    {
        Gla::Timer loop_timer;
        bool should_update_buffers = false;

        // terrain_vertices.clear();
        // transparent_texture_vertices.clear();

        unsigned int size_nontransparent = 0;
        unsigned int size_transparent = 0;

        for (int i = player.ChunkX() - VIEW_DISTANCE; i < player.ChunkX() + VIEW_DISTANCE; i++)
        { // for each chunk in view
            for (int j = player.ChunkZ() - VIEW_DISTANCE; j < player.ChunkZ() + VIEW_DISTANCE; j++)
            {
                // Generates surrounding chunks
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if (Chunk::chunks[k][l] == nullptr) {
                            Chunk::chunks[k][l] = new Chunk(k, l);
                        }
                    }
                }

                if (player.ChunkX() != last_frame_chunkcoords.x || player.ChunkZ() != last_frame_chunkcoords.z)
                {
                    should_update_buffers = true;
                }

                if (Chunk::chunks[i][j]->ShouldBeEmplaced())
                {
                    should_update_buffers = true;
                }
                
                Chunk::chunks[i][j]->EmplaceVertices();

                size_nontransparent += Chunk::chunks[i][j]->GetNonTransparentVec().size();
                size_transparent    += Chunk::chunks[i][j]->GetTransparentVec().size();
            }
        }

        // if (Chunk::chunks[player.ChunkX()][player.ChunkZ()] == nullptr) {
        //     throw std::logic_error("Trying to dereference null from main()");
        // }

        float directional_light_height = 70.0f;
        glm::mat4 directional_light_view_mtr = glm::rotate(glm::mat4(1.0f), glm::radians(300.0f), x_axis) * glm::rotate(glm::mat4(1.0f), glm::radians(300.0f), y_axis)
        * glm::translate(glm::mat4(1.0f), glm::vec3(-player.GetX(), -directional_light_height, -player.GetZ()));  // For now sun is at player's beginning coords
        float planes_lenght = VIEW_DISTANCE * CHUNK_LENGHT * 2.0f;
        glm::mat4 directional_light_proj_mtr = glm::ortho(-planes_lenght, planes_lenght, -planes_lenght, planes_lenght, -planes_lenght, planes_lenght);
        shadow_shader.Bind();
        shadow_shader.SetUniformMat4f("u_SunMvp", directional_light_proj_mtr * directional_light_view_mtr);
        world_shader.Bind();
        world_shader.SetUniformMat4f("u_SunMvp_", directional_light_proj_mtr * directional_light_view_mtr);

        Gla::Timer update_timer;
        float update_time;

        if (should_update_buffers)
        {
            //* World vb update
            world_vb.UpdateSizeIfShould(size_nontransparent * sizeof(float));

            unsigned int offset = 0;

            for (int i = player.ChunkX() - VIEW_DISTANCE; i < player.ChunkX() + VIEW_DISTANCE; i++)
            { // for each chunk
                for (int j = player.ChunkZ() - VIEW_DISTANCE; j < player.ChunkZ() + VIEW_DISTANCE; j++)
                {
                    world_vb.UpdateData(Chunk::chunks[i][j]->GetNonTransparentVec().data(), Chunk::chunks[i][j]->GetNonTransparentVec().size() * sizeof(float), offset);
                    offset += Chunk::chunks[i][j]->GetNonTransparentVec().size() * sizeof(float);
                }
            }

            //* Transparent vb update
            transparent_vb.UpdateSizeIfShould(size_transparent * sizeof(float));

            offset = 0;

            for (int i = player.ChunkX() - VIEW_DISTANCE; i < player.ChunkX() + VIEW_DISTANCE; i++)
            { // for each chunk
                for (int j = player.ChunkZ() - VIEW_DISTANCE; j < player.ChunkZ() + VIEW_DISTANCE; j++)
                {   // The buffer is bound in UpdateData func
                    transparent_vb.UpdateData(Chunk::chunks[i][j]->GetTransparentVec().data(), Chunk::chunks[i][j]->GetTransparentVec().size() * sizeof(float), offset);
                    offset += Chunk::chunks[i][j]->GetTransparentVec().size() * sizeof(float);
                }
            }
        }

        update_time = update_timer.GetTime();


        Gla::Timer render_timer;
        float render_time;

        //* renders sky

        renderer.Clear();

        GLCall( glDisable(GL_DEPTH_TEST) );  // Disables depth test because it shouldn't apply to the sky

        sky_mesh.Bind();
        renderer.DrawArrays(GL_TRIANGLES, 6);

        GLCall( glEnable(GL_DEPTH_TEST) );

        //* rendering shadowmap

        shadowmap_framebuffer.Bind();
        GLCall( glClear(GL_DEPTH_BUFFER_BIT) );

        shadow_mesh_nontransparent.Bind();
        renderer.DrawArrays(draw_mode, size_nontransparent / ELEMENTS_PER_VERTEX);
        shadow_mesh_transparent.Bind();
        renderer.DrawArrays(draw_mode, size_transparent / ELEMENTS_PER_VERTEX);

        Gla::FrameBuffer::BindToDefaultFB(WINDOW_WIDTH, WINDOW_HEIGHT);

        //* draws nontransparent

        bind_textures(NON_TRANSPARENT);
        world_mesh.Bind();
        renderer.DrawArrays(draw_mode, size_nontransparent / ELEMENTS_PER_VERTEX);

        //* draws transparent

        bind_textures(TRANSPARENT);
        transparent_mesh.Bind();
        renderer.DrawArrays(draw_mode, size_transparent / ELEMENTS_PER_VERTEX);

        render_time = render_timer.GetTime();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        renderer.Flush();

        HandleEvents(window);
        player.GravityAcc();
        player.UpdateView();
        last_frame_chunkcoords.x = player.ChunkX();
        last_frame_chunkcoords.z = player.ChunkZ();

        // if (loop_timer.GetTime() < Gla::Timer::FPS60_frame_time)  // FPS limit to 60
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds( (int)((Gla::Timer::FPS60_frame_time - loop_timer.GetTime()) * 1000.0f) ));
        // }
        
        if (out_of_loop_timer.GetTime() >= WINDOW_TITLE_UPDATE_TIME)
        {
            // C++ std::string code

            std::string new_title = "Minecraft - "
            + std::to_string(1 / Gla::Timer::DeltaTime()/*time from last frame*/) + " FPS \\ " + std::to_string(Gla::Timer::DeltaTime()) + " ms \\ "
            + " --- X/Y/Z: " + std::to_string(player.x_pos) + " / " + std::to_string(player.y_pos) + " / " + std::to_string(player.z_pos) + " \\ "
            + "Update time %" + std::to_string((update_time / loop_timer.GetTime()) * 100.0f) + " - "
            + "Render time %" + std::to_string((render_time / loop_timer.GetTime()) * 100.0f);

            #ifdef GLA_DEBUG
                new_title += " ~Debug Mode~";
            #endif

            glfwSetWindowTitle(window, new_title.c_str());
            out_of_loop_timer.Reset();
            
            // C-style string code - should be faster
            /*char title[256];
            title[255] = '\0';

            snprintf(title, 255, "Minecraft - %f FPS  %s",
                1 / Gla::Timer::DeltaTime(), // Last frame time - shows FPS from the previous frame

                #ifdef GLA_DEBUG 
                    "~Debug Mode~\0"
                #else
                    "\0"
                #endif
            );
            
            glfwSetWindowTitle(window, title);

            out_of_loop_timer.Reset();*/
        }

        // if (loop_timer.GetTime() < Gla::Timer::FPS60_frame_time)  // FPS limit to 60
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds( (int)((Gla::Timer::FPS60_frame_time - loop_timer.GetTime()) * 1000.0f) ));
        // }

        Gla::Timer::CalculateDeltaTime(loop_timer.GetTime());
    }

    Chunk::FreeChunkData();

    } // without this block, vb and ib go out of scope after glfwTerminate, and all OpenGL functions in destructors would become totally useless
    
    glfwTerminate();

    return 0;
}