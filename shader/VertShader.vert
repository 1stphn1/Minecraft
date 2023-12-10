#version 460 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TexCoord;
layout(location = 2) in float a_Face;

layout(std140, binding = 0) uniform u_ViewProjectionMatrix
{
    mat4 u_Mvp;
};

out vec2 v_TexCoord;
flat out float v_Face;

void main()
{
    gl_Position = u_Mvp * vec4(a_Position, 1.0f);
    
    v_TexCoord = a_TexCoord;
    v_Face = a_Face;
}