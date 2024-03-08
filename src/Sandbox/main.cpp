#include <cml.h>

#include "Controller/GameController.hpp"
#include "Scene/Scene.hpp"
#include "Rendering/Camera.hpp"
#include "Rendering/Model.hpp"
#include "ObjectTree/GameObject.hpp"

class Entity : public GameObject {
public:
    Model model = Model("Res\\Models\\sus.glb");
    Shader shader = Shader("Res\\Shaders\\GeometryPass.glsl");
    Entity()
    {   mat4 model = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        shader.SetUniformMat4f("u_Model", model);
    }

    void OnUpdate() override
    {
        shader.SetUniformMat4f("u_View", GameController::GameCamera->GetViewMatrix());
        shader.SetUniformMat4f("u_Projection", GameController::GameCamera->GetProjectionMatrix());
    }

    void OnRender() override
    {
        for(auto& mesh: model.GetMeshes())
        {
            for(size_t i = 0; i < mesh.textures.size(); ++i)
            {
                mesh.textures[i].Bind(i);
            }
            GameController::GameRenderer.DrawTriangleMesh(*mesh.va, *mesh.ib, shader);

        }
    }

private:

};

void segvHandler(int s)
{
    printf("Segmentation Fault\n");
    exit(EXIT_FAILURE);
}

int main(void) {
    GameController::OnStart();
    PerspectiveCam cam(45, 0.1, 1000, WINDOW_WIDTH, WINDOW_HEIGHT);
    cam.m_Window = &GameController::RenderTarget;
    GameController::GameCamera = &cam;
    auto scene = Scene();
    Entity suzane;

    scene.GetObjectTree().push_back(&suzane);

    GameController::Scenes[GameController::CurrentScene] = scene;


    while(!GameController::RenderTarget.windowShouldClose())
    {
        GameController::OnUpdate();
        GameController::OnRender();
    }
    return 0;
}