#include "Animation.hpp"

Animation::Animation(const std::string& animationPath, Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    m_TicksPerSecond = animation->mTicksPerSecond;
    ReadHierarchyData(m_RootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Animation::~Animation() {}

Bone* Animation::FindBone(const std::string& name)
{
    auto iter = std::find_if(m_Bones.begin(), m_Bones.end(), 
    [&](const Bone& bone) { 
        return bone.GetBoneName() == name; 
    });

    if(iter == m_Bones.end()) return nullptr;
    else return &(*iter);
}

float Animation::GetTicksPerSecond() { return m_TicksPerSecond; }
float Animation::GetDuration() { return m_Duration; }
const AssimpNodeData& Animation::GetRootNode() { return m_RootNode; }
const std::unordered_map<std::string, BoneInfo>& Animation::GetBoneIDMap() { return m_BoneInfoMap; }

void Animation::ReadMissingBones(const aiAnimation* animation, Model& model)
{
    int size = animation->mNumChannels;
    auto& boneInfoMap = model.GetBoneInfoMap();
    int& boneCount = model.GetBoneCount();

    for(int i = 0; i < size; ++i)
    {
        auto chanel = animation->mChannels[i];
        std::string boneName = chanel->mNodeName.data;

        if(boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCount++;
            // boneCount++;
        }
        m_Bones.push_back(Bone(
            chanel->mNodeName.data, 
            boneInfoMap[chanel->mNodeName.data].id, 
            chanel
        ));
    }

    m_BoneInfoMap = boneInfoMap;
}

void Animation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);
    dest.name = src->mName.data;
    dest.transformation = assimpToCmlMatrix(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for(uint32_t i = 0; i < src->mNumChildren; ++i)
    {
        AssimpNodeData newData;
        ReadHierarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}

