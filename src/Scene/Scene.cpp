#include "Scene.hpp"

Scene::Scene()
{
    this->m_ObjectTree = {};
}

// Scene::Scene(const Scene& that)
// {
//     this->m_ObjectTree = that.m_ObjectTree;
// }

Scene::~Scene()
{

}

// Scene& Scene::operator=(const Scene& that)
// {
//     this->m_ObjectTree = that.m_ObjectTree;
// }

void Scene::OnUpdate() 
{
    for(auto& obj : m_ObjectTree) {
        obj->OnUpdate();
        // obj->UpdateChilds();
    }
}

void Scene::OnRender() 
{
    for(auto & obj : m_ObjectTree) {
        obj->OnRender();
        // obj->RenderChilds();
    }
}

std::vector<GameObject*>& Scene::GetObjectTree()
{
    return m_ObjectTree;
}
