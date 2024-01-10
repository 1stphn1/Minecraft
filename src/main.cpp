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

constexpr float FPS_UPDATE_TIME = 0.7f;

GLenum draw_mode = GL_TRIANGLES;

struct Point {
    float x;
    float y;
    float z;
};

void KeyboardInput(GLFWwindow* window)
{
    constexpr float FULL_ANGLE = 360.0f;

    glfwPollEvents();
    
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        player.UpdateX(-glm::sin(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized());
        player.UpdateZ(-glm::cos(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized());
        // player.x_pos -= glm::sin(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
        // player.z_pos -= glm::cos(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    } else if (glfwGetKey(window, GLFW_KEY_S))
    {
        // player.UpdateX(glm::sin(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized());
        player.x_pos += glm::sin(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
        player.z_pos += glm::cos(glm::radians(-player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    }

    if (glfwGetKey(window, GLFW_KEY_D))
    {
        player.x_pos += glm::cos(glm::radians(player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
        player.z_pos += glm::sin(glm::radians(player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    }
    else if (glfwGetKey(window, GLFW_KEY_A))
    {
        player.x_pos -= glm::cos(glm::radians(player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
        player.z_pos -= glm::sin(glm::radians(player.xz_angle)) * player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    }
    
    if (glfwGetKey(window, GLFW_KEY_SPACE))
    {
        static Gla::Timer time_after_pushing;

        if (time_after_pushing.GetTime() > 0.2f /*seconds*/)
        {
            player.Jump();
            time_after_pushing.Reset();
        }

        // player.y_pos += player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
    {
        player.y_pos -= player.GetMoveDist() * Gla::Timer::DeltaTimeNormalized();
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT))
    {
        player.xz_angle -= player.GetMoveAngle() * Gla::Timer::DeltaTimeNormalized();

        if (player.xz_angle < 0.0f)
        {
            player.xz_angle = 360.0f + player.xz_angle;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT))
    {
        player.xz_angle += player.GetMoveAngle() * Gla::Timer::DeltaTimeNormalized();

        if (player.xz_angle > 360.0f)
        {
            player.xz_angle = player.xz_angle - 360.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN))
    {
        player.y_angle -= player.GetMoveAngle() * Gla::Timer::DeltaTimeNormalized();
    }
    else if (glfwGetKey(window, GLFW_KEY_UP))
    {
        player.y_angle += player.GetMoveAngle() * Gla::Timer::DeltaTimeNormalized();
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
    {
        static Gla::Timer time_after_pushing;

        if (time_after_pushing.GetTime() > 0.2f /*seconds*/)
        {
            player.ChangeSpeed();
            time_after_pushing.Reset();
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) || glfwGetKey(window, GLFW_KEY_ENTER))
    {
        static Gla::Timer time_after_pushing;

        if (time_after_pushing.GetTime() > 0.2f /*seconds*/)
        {
            Chunk::chunks[player.ChunkX()][player.ChunkZ()]->BreakBlock(player);
            time_after_pushing.Reset();
        }
    }

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

// For glfwCursorPosCallback()
static void cursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    static double old_x_pos = WINDOW_WIDTH / 2;
    static double old_y_pos = WINDOW_HEIGHT / 2;
    
    player.xz_angle += (x_pos - old_x_pos) * 0.7;
    player.y_angle  += (y_pos - old_y_pos) * 0.7;

    if (player.xz_angle < 0.0f)
    {
        player.xz_angle = 360.0f + player.xz_angle;
    }
    else if (player.xz_angle > 360.0f)
    {
        player.xz_angle = player.xz_angle - 360.0f;
    }
    
    /*reverse until this does not delete*/

    old_x_pos = x_pos;
    old_y_pos = y_pos;
}

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

int main(int argc, char *argv[])
{
    #ifdef GLA_DEBUG
        std::cout << "\n~In debug mode~\n";
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

    glfwSetCursorPosCallback(window, cursorPosCallback);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Glew init error\n";
    }

    std::cout << glGetString(GL_VERSION) << '\n';

    GLCall( glEnable(GL_DEPTH_TEST) );
    GLCall( glDepthFunc(GL_GREATER) );

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {  // without this block, vb and ib go out of scope after glfwTerminate, so glDeleteBuffers in destructors of IndexBuffer and VertexBuffer doesn't work
    glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, -8.0f, 8.0f) * glm::perspective<float>(glm::radians(10.0f), 1280.0f / 960.0f, 0.1f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(player.x_pos, player.y_pos, player.z_pos));

    const Gla::Texture2D grass_texture("assets/grass.png");
    const Gla::Texture2D grassnd_texture("assets/grassnd.png");
    const Gla::Texture2D dirt_texture("assets/dirt.png");
    const Gla::Texture2D log_texture("assets/log_side.png");
    const Gla::Texture2D stone_texture("assets/stone.png");
    const Gla::Texture2D sand_texture("assets/sand.png");
    const Gla::Texture2D leaves_texture("assets/leaves.png", Gla::GLMinMagFilter::NEAREST);
    const Gla::Texture2D water_texture("assets/water.png", Gla::GLMinMagFilter::NEAREST);

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
            break;
        case TRANSPARENT:
            GLCall( glBindTextureUnit(0, leaves_texture.GetID()) );
            GLCall( glBindTextureUnit(1, water_texture.GetID()) );
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
    // Gla::Shader shadow_shader("shader/ShadowVertShader.vert", "shader/ShadowFragShader.frag");

    Gla::Mesh world_mesh(world_va, world_shader);
    // Gla::Mesh shadow_mesh(world_va, shadow_shader);

    world_shader.Bind();
    int sampler_data[] = { 0, 1, 2, 3, 4, 5 };
    world_shader.SetUniform1iv("u_Samplers", 6, sampler_data);

    Gla::UniformBuffer ubo(0, &PROJECTION_MTR[0][0]);  // This is used in the 'Player' class to update the view projection matrix
    Gla::UniformBuffer ubo_sun(1, &PROJECTION_MTR[0][0]);  // This is used in the 'Player' class to update the view projection matrix
    ubo.Bind();
    // ubo_sun.Bind();

    player.SetUniformBuffer(ubo);

    Gla::Timer out_of_loop_timer;

    /* Game loop */
    while (!glfwWindowShouldClose(window))
    {
        Gla::Timer loop_timer;

        renderer.Clear();

        // terrain_vertices.clear();
        // transparent_texture_vertices.clear();

        GLCall( glDisable(GL_DEPTH_TEST) );  // Disables depth test because it shouldn't apply to the sky

        sky_mesh.Bind();
        renderer.DrawArrays(GL_TRIANGLES, 6);

        GLCall( glEnable(GL_DEPTH_TEST) );

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
                
                Chunk::chunks[i][j]->EmplaceVertices();

                size_nontransparent += Chunk::chunks[i][j]->GetNonTransparentVec().size();
                size_transparent    += Chunk::chunks[i][j]->GetTransparentVec().size();
            }
        }

        // if (Chunk::chunks[player.ChunkX()][player.ChunkZ()] == nullptr) {
        //     throw std::logic_error("Trying to dereference null from main()");
        // }

        //* draws nontransparent

        bind_textures(NON_TRANSPARENT);
        world_mesh.Bind();

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

        renderer.DrawArrays(draw_mode, size_nontransparent / ELEMENTS_PER_VERTEX);

        //*


        // bind_textures(NON_TRANSPARENT);
        // world_mesh.Bind();

        // world_vb.UpdateSizeIfShould(terrain_vertices.size() * sizeof(float));
        // world_vb.UpdateData(terrain_vertices.data(), terrain_vertices.size() * sizeof(float));
        // renderer.DrawArrays(draw_mode, terrain_vertices.size() / ELEMENTS_PER_VERTEX);

        //* draws transparent

        bind_textures(TRANSPARENT);
        transparent_mesh.Bind();

        transparent_vb.UpdateSizeIfShould(size_transparent * sizeof(float));

        offset = 0;

        for (int i = player.ChunkX() - VIEW_DISTANCE; i < player.ChunkX() + VIEW_DISTANCE; i++)
        { // for each chunk
            for (int j = player.ChunkZ() - VIEW_DISTANCE; j < player.ChunkZ() + VIEW_DISTANCE; j++)
            {
                transparent_vb.UpdateData(Chunk::chunks[i][j]->GetTransparentVec().data(), Chunk::chunks[i][j]->GetTransparentVec().size() * sizeof(float), offset);
                offset += Chunk::chunks[i][j]->GetTransparentVec().size() * sizeof(float);
            }
        }

        renderer.DrawArrays(draw_mode, size_transparent / ELEMENTS_PER_VERTEX);

        //*

        // bind_textures(TRANSPARENT);
        // transparent_mesh.Bind();

        // transparent_vb.UpdateSizeIfShould(transparent_texture_vertices.size() * sizeof(float));
        // transparent_vb.UpdateData(transparent_texture_vertices.data(), transparent_texture_vertices.size() * sizeof(float));
        // renderer.DrawArrays(draw_mode, transparent_texture_vertices.size() / ELEMENTS_PER_VERTEX);

        // Chunk::FreeUnneededVertexData();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        renderer.Flush();

        KeyboardInput(window);
        player.GravityAcc();
        player.UpdateView();

        if (loop_timer.GetTime() < Gla::Timer::FPS60_frame_time) {  // Frame limit 60 fps
            std::this_thread::sleep_for(std::chrono::milliseconds( (int)((Gla::Timer::FPS60_frame_time - loop_timer.GetTime()) * 1000.0f) ));
        }
        
        if (out_of_loop_timer.GetTime() >= FPS_UPDATE_TIME) {
            // C++ std::string code

            std::string new_title = "Minecraft - "
            + std::to_string(1 / Gla::Timer::DeltaTime()/*time from last frame*/) + " FPS \\ " + std::to_string(Gla::Timer::DeltaTime()) + " ms \\ "
            + " --- X/Y/Z: " + std::to_string(player.x_pos) + " / " + std::to_string(player.y_pos) + " / " + std::to_string(player.z_pos);

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

        Gla::Timer::CalculateDeltaTime(loop_timer.GetTime());
    }

    Chunk::FreeChunkData();

    } // without this block, vb and ib go out of scope after glfwTerminate, and all OpenGL functions in destructors would become totally useless
    
    glfwTerminate();

    return 0;
}