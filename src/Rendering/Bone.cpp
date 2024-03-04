#include "Bone.hpp"
#include <Util/assimpHelpers.hpp>
#include <assert.h>

Bone::Bone(const std::string& name, int id, const aiNodeAnim* chanel)
    :m_Name(name), m_ID(id), m_LocalTransform(cml::identity4)
{
    m_NumPositions = chanel->mNumPositionKeys;

    for(int positionIndex = 0; positionIndex < m_NumPositions; ++positionIndex)
    {
        aiVector3D aiPosition = chanel->mPositionKeys[positionIndex].mValue;
        float timeStamp = chanel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = assimpToCmlVect(aiPosition);
        data.timeStamp = timeStamp;
        m_Positions.push_back(data);
    }

    m_NumRotations = chanel->mNumRotationKeys;
    for(int rotationIndex = 0; rotationIndex < m_NumRotations; ++rotationIndex)
    {
        aiQuaternion aiOrientation = chanel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = chanel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = assimpToCmlQuat(aiOrientation);
        data.timeStamp = timeStamp;
        m_Rotations.push_back(data);
    }

    m_NumScalings = chanel->mNumScalingKeys;
    for(int keyIndex = 0; keyIndex < m_NumScalings; ++keyIndex)
    {
        aiVector3D scale = chanel->mScalingKeys[keyIndex].mValue;
        float timeStamp = chanel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = assimpToCmlVect(scale);
        data.timeStamp = timeStamp;
        m_Scales.push_back(data);
    }

}

void Bone::Update(float animationTime)
{
    mat4 translation = InterpolatePosition(animationTime);
    mat4 rotation = InterpolateRotation(animationTime);
    mat4 scale = InterpolateScaling(animationTime);

    m_LocalTransform = translation * rotation * scale;
}

mat4 Bone::GetLocalTransform() const { return m_LocalTransform; }

std::string Bone::GetBoneName() const { return m_Name; }

int Bone::GetBoneID() const { return m_ID; }

int Bone::GetPostitionIndex(float animationTime)
{
    for(int index = 0; index < m_NumPositions - 1; ++index)
    {
        if(animationTime < m_Positions[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int Bone::GetRotationIndex(float animationTime)
{
    for(int index = 0; index < m_NumRotations - 1; ++index)
    {
        if(animationTime < m_Rotations[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

int Bone::GetScaleIndex(float animationTime)
{
    for(int index = 0; index < m_NumScalings - 1; ++index)
    {
        if(animationTime < m_Scales[index + 1].timeStamp)
            return index;
    }
    assert(0);
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    float scaleFactor = 0.0f;
    float midWayLenght = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLenght / framesDiff;
    return scaleFactor;
}

mat4 Bone::InterpolatePosition(float animationTime)
{
    if(1 == m_NumPositions)
        return cml::translate(cml::identity4, m_Positions[0].position);
    
    int p0Index = GetPostitionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(
        m_Positions[p0Index].timeStamp,
        m_Positions[p1Index].timeStamp,
        animationTime
    );

    vec3 finalPosition = cml::mix(
        m_Positions[p0Index].position,
        m_Positions[p1Index].position,
        scaleFactor
    );

    return cml::translate(cml::identity4, finalPosition);
}

mat4 Bone::InterpolateRotation(float animationTime)
{
    if(1 == m_NumRotations)
    {
        quat rotation = cml::norm(m_Rotations[0].orientation);
        return rotation.toMat4();
    }

    int p0Index = GetRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(
        m_Rotations[p0Index].timeStamp,
        m_Rotations[p1Index].timeStamp,
        animationTime
    );

    quat finalRotation = cml::slerp(
        m_Rotations[p0Index].orientation,
        m_Rotations[p1Index].orientation,
        scaleFactor
    );

    finalRotation = cml::norm(finalRotation);
    return finalRotation.toMat4();
}

mat4 Bone::InterpolateScaling(float animationTime)
{
    if(1 == m_NumScalings)
        return cml::scale(cml::identity4, m_Scales[0].scale);

    int p0Index = GetScaleIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(
        m_Scales[p0Index].timeStamp,
        m_Scales[p1Index].timeStamp,
        animationTime
    );

    vec3 finalScale = cml::mix(
        m_Scales[p0Index].scale,
        m_Scales[p1Index].scale,
        scaleFactor
    );

    return cml::scale(cml::identity4, finalScale);
}
