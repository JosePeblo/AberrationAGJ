#pragma once
#include <vector>

class GameObject
{
public:
    GameObject(){};

    // ~GameObject(); // I Destructor
    // GameObject(const GameObject&); // II Copy copy constructor
    // GameObject& operator=(const GameObject&); //III Copy assignment operator { return *this; }

    // GameObject(GameObject&&) noexcept; // IV Move constructor
    // GameObject& operator=(GameObject&&) noexcept; // V Move assignment operator

    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

    // virtual void UpdateChilds() = 0;
    // virtual void RenderChilds() = 0;


protected:
    std::vector<GameObject*> m_children;
private:

};
