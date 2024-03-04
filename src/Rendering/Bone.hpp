#pragma once
#include <vector>
#include <string>
#include <assimp/anim.h>
#include <cml.h>

struct KeyPosition {
    vec3 position;
    float timeStamp;
};

struct KeyRotation {
    quat orientation;
    float timeStamp;
};

struct KeyScale {
    vec3 scale;
    float timeStamp;
};

class Bone {
public:
    Bone() = delete;
    // Bone(const Bone&) = delete;
    Bone(const std::string& name, int id, const aiNodeAnim* chanel);
    void Update(float animationTime);

    mat4 GetLocalTransform() const;
    std::string GetBoneName() const;
    int GetBoneID() const;

    int GetPostitionIndex(float animationTime);
    int GetRotationIndex(float animationTime);
    int GetScaleIndex(float animationTime);

private:
    float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
    mat4 InterpolatePosition(float animationTime);
    mat4 InterpolateRotation(float animationTime);
    mat4 InterpolateScaling(float animationTime);


private:
    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;
    int m_NumPositions;
    int m_NumRotations;
    int m_NumScalings;

    std::string m_Name;
    int m_ID;
    mat4 m_LocalTransform;
};
