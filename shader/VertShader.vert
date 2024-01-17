#version 460 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TexCoord;
layout(location = 2) in float a_Face;

layout(binding = 0) uniform u_ViewProjectionMatrix
{
    mat4 u_Mvp;
};

uniform mat4 u_SunMvp;

out vec2 v_TexCoord;
flat out float v_Face;
// flat out float v_LightIntensity;

void main()
{
    gl_Position = u_Mvp * vec4(a_Position, 1.0f);
    
    v_TexCoord = a_TexCoord;
    v_Face = a_Face;

    // vec4 pos = u_SunMvp * vec4(a_Position, 1.0f);

    // if (pos.z > 0.0 && pos.x > -pos.w && pos.x < pos.w && pos.y > -pos.w && pos.y < pos.w) {
    //     // The sun can see the vertex
    //     v_LightIntensity = 1.0f;
    // } else {
    //     // The sun cannot see the vertex
    //     v_LightIntensity = 0.6f;
    // }
}