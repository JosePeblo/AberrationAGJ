#include "Model.hpp"
#include <assert.h>
#include <Util/assimpHelpers.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Model::Model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        printf("ERROR::ASSIMP::%s\n", importer.GetErrorString());
        return;
    }
    std::string directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::SetVertexBoneDataToDefault(Vertex& vertex)
{
    for(int i = 0; i < MAX_BONE_WEIGHTS; ++i)
    {
        vertex.boneIds[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    Mesh ms;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Tx> textures;
    
    // Vertices
    for(uint32_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;

        SetVertexBoneDataToDefault(vertex);

        vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0])
        {
            vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } 
        else 
        {
            vertex.TexCoords = { 0.0f, 0.0f };
        }

        vertices.push_back(vertex);
    }

    // Indices
    for(uint32_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    ExtractBoneWeigthsForVertices(vertices, mesh, scene);

    // for(const auto& v : vertices)
    // {
    //     std::cout << v.boneIds[0] << ", " << v.boneIds[1] << ", " << v.boneIds[2] << ", " << v.boneIds[3] << "\n";
    // }

    ms.vertices = vertices;
    ms.indices = indices;
    ms.vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
    ms.va = new VertexArray();
    ms.layout.Push<float>(3);          // Layout 0: position
    ms.layout.Push<float>(3);          // Layout 1: normal
    ms.layout.Push<float>(2);          // Layout 2: tex coords
    ms.layout.Push<int>(4);            // Layout 3: bone ids
    ms.layout.Push<float>(4);          // Layout 4: bone weights
    ms.va->AddBuffer(*ms.vb, ms.layout);
    ms.ib = new IndexBuffer(&indices[0], indices.size());
    
    return ms;
}

void Model::ExtractBoneWeigthsForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
    for(uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneId = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if((m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end()))
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = m_BoneCounter;
            newBoneInfo.offset = assimpToCmlMatrix(mesh->mBones[boneIndex]->mOffsetMatrix);
            m_BoneInfoMap[boneName] = newBoneInfo;
            boneId = m_BoneCounter++;
        }
        else 
        {
            boneId = m_BoneInfoMap[boneName].id;
        }
        assert(boneId != -1);

        printf("Bone %d: %s\n", boneId, boneName.c_str());

        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for(int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= (int)vertices.size());
            SetVertexBoneData(vertices[vertexId], boneId, weight);
        }
    }
}

void Model::SetVertexBoneData(Vertex& vertex, int boneID, float weight)
{
    for(int i = 0; i < MAX_BONE_WEIGHTS; ++i)
    {
        if(vertex.boneIds[i] < 0)
        {
            vertex.weights[i] = weight;
            vertex.boneIds[i] = boneID;
            break;
        }
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for(uint32_t i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }

    for(uint32_t i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}
