#version 460 core

layout(location = 0) in vec3  a_Position;
// layout(location = 1) in vec2  a_TexCoord;
// layout(location = 2) in float a_Face;

uniform mat4 u_SunMvp;

void main()
{
    gl_Position = u_SunMvp * vec4(a_Position, 1.0f);
}