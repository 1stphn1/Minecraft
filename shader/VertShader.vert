#version 460 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec2  a_TexCoord;
layout(location = 2) in float a_Face;

layout(binding = 0) uniform u_ViewProjectionMatrix
{
    mat4 u_Mvp;
};

out vec2 v_TexCoord;
out vec4 v_LightSpacePos;
flat out float v_Face;
// flat out float v_LightIntensity;

uniform mat4 u_SunMvp_;

void main()
{
    vec4 position = vec4(a_Position, 1.0f);

    gl_Position = u_Mvp * position;
    
    v_TexCoord = a_TexCoord;
    v_Face = a_Face;
    v_LightSpacePos = u_SunMvp_ * position;

    // vec4 pos = u_SunMvp * vec4(a_Position, 1.0f);

    // if (pos.z > 0.0 && pos.x > -pos.w && pos.x < pos.w && pos.y > -pos.w && pos.y < pos.w) {
    //     // The sun can see the vertex
    //     v_LightIntensity = 1.0f;
    // } else {
    //     // The sun cannot see the vertex
    //     v_LightIntensity = 0.6f;
    // }
}