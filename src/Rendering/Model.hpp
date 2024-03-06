#pragma once
#include <unordered_map>
#include <string>
#include <assimp/scene.h>

#include "Mesh.hpp"

typedef struct {
    int id;
    mat4 offset;
} BoneInfo;

class Model {
public:
    Model() = default;
    Model(const std::string& path);
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }
    std::vector<Mesh>& GetMeshes() { return m_Meshes; }

private:
    std::vector<Mesh> m_Meshes;
    std::unordered_map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

    void SetVertexBoneDataToDefault(Vertex& vertex);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void ExtractBoneWeigthsForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    void processNode(aiNode* node, const aiScene* scene);
    void loadMaterialTextures(std::vector<Texture>& textures, aiMaterial* mat, aiTextureType type, const std::string& typeName);

};
