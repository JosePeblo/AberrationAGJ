#pragma once
#include "Renderer.h"

class RenderBuffer {
public:
    RenderBuffer() = default;
    ~RenderBuffer();
    RenderBuffer(uint32_t width, uint32_t height);
    RenderBuffer(const RenderBuffer&) = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;
    RenderBuffer& operator=(RenderBuffer&&) noexcept;
    void Bind() const;
    void Unbind() const;
    inline uint32_t GetID();
private:
    uint32_t m_rendererID = 0;
};
