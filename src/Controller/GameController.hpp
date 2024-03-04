#pragma once
#include <vector>
#include "pbgl/pbgl.h"

#include "Scene/Scene.hpp"
#include "Scene/Window.hpp"
#include "AssetManager/Asset.hpp"
#include "Rendering/Camera.hpp"

#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 400

namespace GameController {
inline Renderer GameRenderer;
inline std::vector<Scene> Scenes = { Scene() };
inline uint32_t CurrentScene = 0;
// inline std::vector<Asset> Assets;
inline Window RenderTarget(WINDOW_WIDTH, WINDOW_HEIGHT, "Aberrations");
inline Camera* GameCamera = nullptr;
void OnStart();
void OnUpdate();
void OnRender();
// void OnPhysicsUpdate();

// update -> Render all objects -> post process

// Rendering pipeline
inline RenderBuffer depthBuffer;
inline FrameBuffer gBuffer;
inline Texture     gAlbedoSpec;
inline Texture     gPosition;
inline Texture     gNormals;

void GBufferSettup();
};
