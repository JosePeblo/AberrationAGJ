#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <cml.h>
#include <Util/assimpHelpers.hpp>
#include "Model.hpp"
#include "Bone.hpp"

struct AssimpNodeData{
    mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation {
public:
    Animation() = default;
    Animation(const std::string& animationPath, Model* model);
    ~Animation();

    Bone* FindBone(const std::string& name);

    float GetTicksPerSecond();
    float GetDuration();
    const AssimpNodeData& GetRootNode();
    const std::unordered_map<std::string, BoneInfo>& GetBoneIDMap();

private:
    void ReadMissingBones(const aiAnimation* animation, Model& model);
    void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

    float m_Duration;
    int m_TicksPerSecond;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::unordered_map<std::string, BoneInfo> m_BoneInfoMap;

};
