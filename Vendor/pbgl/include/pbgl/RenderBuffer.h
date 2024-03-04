#pragma once
#include "Renderer.h"

class RenderBuffer {
public:
    RenderBuffer() = default;
    ~RenderBuffer();
    RenderBuffer(uint32_t width, uint32_t height);
    void Bind() const;
    void Unbind() const;
private:
    uint32_t m_rendererID = 0;
};
