#shader vertex
#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 0.0f, 1.0f);
    v_TexCoord = a_TexCoord;
    // v_TexCoord = a_Position + 0.5f;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Sampler;

void main()
{
    // color = texture(u_Sampler, vec2(0.0f, 0.0f));
    color = texture(u_Sampler, v_TexCoord);
}