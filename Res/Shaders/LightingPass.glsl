#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 v_TexCoords;

void main()
{
    gl_Position = vec4(position, 1.0);
    v_TexCoords = uv;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormals;
uniform sampler2D u_gAlbedoSpec;

void main()
{
    const vec3 camPos = vec3(2.0, 1.0, 0.0);

    color = texture(u_gAlbedoSpec, v_TexCoords);
    // vec3 normal = texture(u_gNormals, v_TexCoords).xyz;

    // color.xyz *= dot(camPos, normal);

}
