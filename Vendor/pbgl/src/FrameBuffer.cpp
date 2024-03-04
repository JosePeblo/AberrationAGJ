#include "pbgl/FrameBuffer.h"
#include "pbgl/Renderer.h"
#include <glad/glad.h>

FrameBuffer::FrameBuffer() 
{
    GLCall(glGenFramebuffers(1, &m_rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

FrameBuffer::FrameBuffer(const Texture& renderTexture) {
    GLCall(glGenFramebuffers(1, &m_rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));
    
    GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture.m_rendererID, 0));
    
    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    GLCall(glDrawBuffers(1, drawBuffers));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        puts("Frame buffer error");

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    //glViewport(0, 0, screen.x, screen.y);
    // TODO: depth buffer and stencil buffer
}

FrameBuffer::~FrameBuffer() {
    if(m_rendererID) {
        GLCall(glDeleteFramebuffers(1, &m_rendererID));
        m_rendererID = 0;
    }
}

void FrameBuffer::Bind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID));
}

void FrameBuffer::Unbind() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Clear() {
    this->Bind();
    GLuint clearColor[4] = { 0, 0, 0, 0 };
    GLCall(glClearBufferuiv(GL_COLOR, 0, clearColor));
    this->Unbind();
}

void FrameBuffer::AttachRenderTextures(const std::vector<Texture*>& textures)
{
    if(textures.size() == 0) return;

    // Sorry
    uint32_t* attachments = new uint32_t[textures.size()];
    for(uint32_t i = 0; i < textures.size(); ++i)
    {
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_attachments++, GL_TEXTURE_2D, textures[i]->m_rendererID, 0));
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    GLCall(glDrawBuffers(textures.size(), attachments));
    delete attachments;

}

