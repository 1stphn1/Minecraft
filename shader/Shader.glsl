#shader vertex
#version 460 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TexCoord;
layout(location = 2) in float a_Slot;

uniform mat4 u_MVP;

out vec2 v_TexCoord;
flat out int v_Slot;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 1.0f);

    v_TexCoord = a_TexCoord;
    v_Slot = int(a_Slot);
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

#define GRASS_TEXTURE 0
#define DIRT_TEXTURE  2

uniform sampler2D u_Sampler;

in vec2 v_TexCoord;
flat in int v_Slot;

void main()
{
    color = texture(u_Sampler, v_TexCoord);
}