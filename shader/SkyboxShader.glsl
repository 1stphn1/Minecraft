#shader vertex
#version 460 core

layout(location = 0) in vec3 position;

out vec3 v_TexCoord;

uniform mat4 u_ProjView;
uniform vec3 u_CameraPos;

void main()
{
    gl_Position = u_ProjView * (vec4(position, 1.0f) - vec4(u_CameraPos, 0.0f));
    v_TexCoord = position;
}

#shader fragment
#version 460 core

out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube u_SkyBox;

void main()
{
    color = texture(u_SkyBox, v_TexCoord);
}