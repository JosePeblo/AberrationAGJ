#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 uv;
layout(location = 3) in ivec4 boneIds;
layout(location = 4) in vec4 weights;

out vec2 v_TexCoords;
out vec3 v_FragPos;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec4 pos = u_Projection * u_View * u_Model * vec4(position, 1.0f);

    gl_Position = pos;
    v_TexCoords = uv;
    v_FragPos = vec4(u_Model * vec4(position, 1.0f)).xyz;
    v_Normal = norm;
}

#shader fragment
#version 460 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in vec2 v_TexCoords;
in vec3 v_FragPos;
in vec3 v_Normal;

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;

void main()
{
    gPosition       = v_FragPos;
    gNormal         = normalize(v_Normal);
    gAlbedoSpec.rgb = texture(u_diffuse, v_TexCoords).rgb;
    gAlbedoSpec.a   = texture(u_specular, v_TexCoords).a;

}
