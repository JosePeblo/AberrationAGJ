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

struct Rect {
    const float vertices[24] = { 
        //Coords    //TexCoords
        1.f, -1.f,  1.f,  0.f,
       -1.f, -1.f,  0.f,  0.f,
       -1.f,  1.f,  0.f,  1.f,
        
        1.f,  1.f,  1.f,  1.f,
        1.f, -1.f,  1.f,  0.f,
       -1.f,  1.f,  0.f,  1.f,
    };
    const unsigned int indices[6] = {
        0, 1, 2,
        3, 4, 5
    };

    VertexArray* va = nullptr;
    VertexBuffer* vb = nullptr;
    VertexBufferLayout layout;
    IndexBuffer* ib = nullptr;

    inline Rect()
    {
        va = new VertexArray;
        vb = new VertexBuffer(vertices, sizeof(vertices));
        ib = new IndexBuffer(indices, 6);
        layout.Push<float>(2);
        layout.Push<float>(2);

        va->AddBuffer(*vb, layout);
    }

    inline ~Rect()
    {
        if(va) delete va;
        if(vb) delete vb;
        if(ib) delete ib;
    }

};


