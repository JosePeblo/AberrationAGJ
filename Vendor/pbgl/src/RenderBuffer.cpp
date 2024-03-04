#include "pbgl/RenderBuffer.h"
#include <stdio.h>

RenderBuffer::RenderBuffer(uint32_t width, uint32_t height)
{
    GLCall(glGenRenderbuffers(1, &m_rendererID));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rendererID));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rendererID));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        puts("Frame buffer not complete!");

    this->Unbind();
}

RenderBuffer::~RenderBuffer() 
{
    if(m_rendererID)
    {
        GLCall(glDeleteRenderbuffers(1, &m_rendererID));
        m_rendererID = 0;
    }
}

void RenderBuffer::Bind() const 
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rendererID));
}

void RenderBuffer::Unbind() const 
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}
