#include "GameController.hpp"

namespace GameController {

void OnStart() {
    // Rendering pipeline settup
    GBufferSettup();


}

void OnUpdate() {
    RenderTarget.pollEvents();
    Scenes[CurrentScene].OnUpdate();
    if(GameCamera)
        GameCamera->OnUpdate();
}

void OnRender() {
    RenderTarget.clear();

    gBuffer.Bind();
    RenderTarget.clear();
    Scenes[CurrentScene].OnRender();
    gBuffer.Unbind();

    gPosition.Bind(0);
    lightPass.SetUniform1i("u_gPosition", 0);
    gNormals.Bind(1);
    lightPass.SetUniform1i("u_gNormals", 1);
    gAlbedoSpec.Bind(2);
    lightPass.SetUniform1i("u_gAlbedoSpec", 2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    GameRenderer.DrawTriangleMesh(*screenRect.va, *screenRect.ib, lightPass);

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

    depthBuffer = RenderBuffer(RenderTarget.GetDims().x, RenderTarget.GetDims().y);
    depthBuffer.Bind();
}

};