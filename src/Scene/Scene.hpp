#pragma once
#include <vector>
#include "Window.hpp"
#include "ObjectTree/GameObject.hpp"

class Scene {
public:
    Scene();
    ~Scene();
    // Scene(const Scene&);
    // Scene& operator=(const Scene&);

    // Scene(Scene&&) noexcept;


    void OnUpdate();
    void OnRender();

    std::vector<GameObject*>& GetObjectTree();
private:
    std::vector<GameObject*> m_ObjectTree;
};