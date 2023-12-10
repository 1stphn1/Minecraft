#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

varying vec3 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 u_Transform;
uniform vec4 u_Cam;
uniform vec4 u_CenterVec;

void main()
{
    gl_Position = u_Transform * u_MVP * (position + u_Cam) + u_Transform * u_MVP * u_CenterVec;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

varying vec3 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
};