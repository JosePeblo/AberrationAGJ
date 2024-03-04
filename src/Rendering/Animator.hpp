#pragma once
#include "Animation.hpp"
#include <vector>
#include <cml.h>

class Animator {
public:
    Animator(Animation* anim);
    void UpdateAnimation(float dt);
    void PlayAnimation(Animation* pAnimation);
    void CalculateBoneTransform(const AssimpNodeData* node, const mat4 parentTransform);
    std::vector<mat4> GetFinalBoneMatrices();

private:
    std::vector<mat4> m_FinalBoneMatrices;
    Animation* m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
};
