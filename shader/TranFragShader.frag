#version 460 core

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 960

#define FRONT_FACE   0
#define BACK_FACE    1
#define LEFT_FACE    2
#define RIGHT_FACE   3
#define TOP_FACE     4
#define BOTTOM_FACE  5

#define LEAVE_BLOCK  60
#define WATER_BLOCK  70

layout(location = 0) out vec4 color;

uniform sampler2D u_Samplers[2];

in vec2 v_TexCoord;
flat in float v_Face;

void main()
{
    // Frustum culling
    if (gl_FragCoord.x / WINDOW_WIDTH < 0.0f  || gl_FragCoord.x / WINDOW_WIDTH > 1.0f || 
        gl_FragCoord.y / WINDOW_HEIGHT < 0.0f || gl_FragCoord.y / WINDOW_HEIGHT > 1.0f)
    {
        discard;
    }

    float light_intensity = 1.0f;
    
    if (int(v_Face) - (int(v_Face) % 10) == LEAVE_BLOCK)
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
        
        color = texture(u_Samplers[0], v_TexCoord);
    }
    else if (int(v_Face) - (int(v_Face) % 10) == WATER_BLOCK)
    {
        color = texture(u_Samplers[1], v_TexCoord);
    }
    else
    {
        color = vec4(0.07, 0.61, 0.92, 1.0);
    }

    color.r *= light_intensity;
    color.g *= light_intensity;
    color.b *= light_intensity;
}