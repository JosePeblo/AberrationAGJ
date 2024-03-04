#pragma once
#include "Texture.h"
#include "vector"

class FrameBuffer {
    unsigned int m_rendererID;
    uint32_t     m_attachments;
public:
    FrameBuffer();
    FrameBuffer(const Texture& renderTexture);
    // void AttachTexture(const Texture& tex);
    void AttachRenderTextures(const std::vector<Texture*>& textures);
    ~FrameBuffer();
    void Bind();
    void Unbind();
    void Clear();
    
};
