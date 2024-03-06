#pragma once
#include <string>
#include <vector>
#include <cml.h>

#include "pbgl/pbgl.h"

#define MAX_BONE_INFLUENCE 4
#define MAX_BONE_WEIGHTS 4

typedef struct {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;

    // vec3 Tangent;
    // vec3 Bitangent;

    int boneIds[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];

} Vertex;

typedef struct {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;

    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout layout;
    IndexBuffer* ib;
} Mesh;

