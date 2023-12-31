#version 460 core

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 960

#define FRONT_FACE   0
#define BACK_FACE    1
#define LEFT_FACE    2
#define RIGHT_FACE   3
#define TOP_FACE     4
#define BOTTOM_FACE  5

#define GRASS_BLOCK  10
#define DIRT_BLOCK   20
#define TREE_LOG     30
#define STONE_BLOCK  40
#define SAND_BLOCK   50

#define GRASS_TEXTURE   0
#define DIRT_TEXTURE    1
#define GRASSND_TEXTURE 2
#define LOG_TEXTURE     3
#define STONE_TEXTURE   4
#define SAND_TEXTURE    5

layout(location = 0) out vec4 color;

uniform sampler2D u_Samplers[6];

in vec2 v_TexCoord;
flat in float v_Face;

void main()
{
    if (gl_FragCoord.x / WINDOW_WIDTH < 0.0f || gl_FragCoord.x / WINDOW_WIDTH > 1.0f || 
        gl_FragCoord.y / WINDOW_HEIGHT < 0.0f || gl_FragCoord.y / WINDOW_HEIGHT > 1.0f)
    {
        discard;
    }

    float light_intensity = 1.0f;

    if (int(v_Face) - (int(v_Face) % 10) == GRASS_BLOCK)
    {
        switch (int(v_Face) % 10) {
            case FRONT_FACE:
                color = texture(u_Samplers[GRASSND_TEXTURE], v_TexCoord);
                light_intensity = 0.9f;
                break;
            case BACK_FACE:
                color = texture(u_Samplers[GRASSND_TEXTURE], v_TexCoord);
                light_intensity = 0.7f;
                break;
            case LEFT_FACE:
                color = texture(u_Samplers[GRASSND_TEXTURE], v_TexCoord);
                light_intensity = 0.8f;
                break;
            case RIGHT_FACE:
                color = texture(u_Samplers[GRASSND_TEXTURE], v_TexCoord);
                light_intensity = 0.8f;
                break;
            case TOP_FACE:
                color = texture(u_Samplers[GRASS_TEXTURE], v_TexCoord);
                light_intensity = 1.0f;
                break;
            case BOTTOM_FACE:
                color = texture(u_Samplers[DIRT_TEXTURE], v_TexCoord);
                light_intensity = 0.7f;
                break;
        }
    }
    else if (int(v_Face) - (int(v_Face) % 10) == DIRT_BLOCK)
    {
        switch (int(v_Face) % 10) {
            case FRONT_FACE:
                light_intensity = 0.9f;
                break;
            case BACK_FACE:
                light_intensity = 0.7f;
                break;
            case LEFT_FACE:
                light_intensity = 0.8f;
                break;
            case RIGHT_FACE:
                light_intensity = 0.8f;
                break;
            case TOP_FACE:
                light_intensity = 1.0f;
                break;
            case BOTTOM_FACE:
                light_intensity = 0.7f;
                break;
        }
        
        color = texture(u_Samplers[DIRT_TEXTURE], v_TexCoord);
    }
    else if (int(v_Face) - (int(v_Face) % 10) == TREE_LOG)
    {
        switch (int(v_Face) % 10) {
            case FRONT_FACE:
                light_intensity = 0.9f;
                break;
            case BACK_FACE:
                light_intensity = 0.7f;
                break;
            case LEFT_FACE:
                light_intensity = 0.8f;
                break;
            case RIGHT_FACE:
                light_intensity = 0.8f;
                break;
            case TOP_FACE:
                light_intensity = 1.0f;
                break;
            case BOTTOM_FACE:
                light_intensity = 0.7f;
                break;
        }
        
        color = texture(u_Samplers[LOG_TEXTURE], v_TexCoord);
    }
    else if (int(v_Face) - (int(v_Face) % 10) == STONE_BLOCK)
    {
        switch (int(v_Face) % 10) {
            case FRONT_FACE:
                light_intensity = 0.9f;
                break;
            case BACK_FACE:
                light_intensity = 0.7f;
                break;
            case LEFT_FACE:
                light_intensity = 0.8f;
                break;
            case RIGHT_FACE:
                light_intensity = 0.8f;
                break;
            case TOP_FACE:
                light_intensity = 1.0f;
                break;
            case BOTTOM_FACE:
                light_intensity = 0.7f;
                break;
        }
        
        color = texture(u_Samplers[STONE_TEXTURE], v_TexCoord);
    }
    else if (int(v_Face) - (int(v_Face) % 10) == SAND_BLOCK)
    {
        switch (int(v_Face) % 10) {
            case FRONT_FACE:
                light_intensity = 0.9f;
                break;
            case BACK_FACE:
                light_intensity = 0.7f;
                break;
            case LEFT_FACE:
                light_intensity = 0.8f;
                break;
            case RIGHT_FACE:
                light_intensity = 0.8f;
                break;
            case TOP_FACE:
                light_intensity = 1.0f;
                break;
            case BOTTOM_FACE:
                light_intensity = 0.7f;
                break;
        }
        
        color = texture(u_Samplers[SAND_TEXTURE], v_TexCoord);
    }
    else
    {
        color = vec4(0.92f, 0.07f, 0.07f, 1.0f);
    }

    color.r *= light_intensity;
    color.g *= light_intensity;
    color.b *= light_intensity;
}