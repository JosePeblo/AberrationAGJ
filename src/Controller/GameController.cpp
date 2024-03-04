#include "GameController.hpp"

namespace GameController {

void OnStart() {
    // Rendering pipeline settup
    GBufferSettup();


}

void OnUpdate() {
    RenderTarget.pollEvents();
    Scenes[CurrentScene].OnUpdate();
}

void OnRender() {
    RenderTarget.clear();

    gBuffer.Bind();
    RenderTarget.clear();
    Scenes[CurrentScene].OnRender();
    gBuffer.Unbind();
    RenderTarget.swapBuffers();
}

void GBufferSettup() {
    gBuffer.Bind();
    TextureOptions options;
    gAlbedoSpec = Texture(RenderTarget.GetDims().x, RenderTarget.GetDims().y, options);
    options.Format = GL_RGBA16F;
    options.Type   = GL_FLOAT;
    gPosition = Texture(RenderTarget.GetDims().x, RenderTarget.GetDims().y, options);
    gNormals = Texture(RenderTarget.GetDims().x, RenderTarget.GetDims().y, options);
    
    gBuffer.AttachRenderTextures({&gPosition, &gNormals, &gAlbedoSpec});

    depthBuffer = RenderBuffer();
    depthBuffer.Bind();
}

};