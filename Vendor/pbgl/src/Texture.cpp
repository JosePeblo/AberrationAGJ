#include "pbgl/Texture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "pbgl/Renderer.h"

Texture::Texture() { }

Texture::Texture(int width, int height, const TextureOptions& options)
: m_width(width), m_height(height)
{
    CreateTexture(options);
}


void Texture::CreateTexture(const TextureOptions& options, void* ptr/*= nullptr*/)
{
    GLCall(glGenTextures(1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, options.MipLevels, options.Format, m_width, m_height, 0, options.PixFormat, options.Type, ptr));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.MinFilter));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.MagFilter));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.WrapS));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.WrapT));
    
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


Texture::Texture(const char* filePath, int flip) {
    stbi_set_flip_vertically_on_load(flip);
    unsigned char* imgBuffer = stbi_load(filePath, &m_width, &m_height, &m_bpp, 4);
    if(!imgBuffer) return;

    TextureOptions options;
    options.MinFilter = GL_LINEAR;
    options.MagFilter = GL_LINEAR;
    options.WrapS     = GL_CLAMP_TO_EDGE;
    options.WrapT     = GL_CLAMP_TO_EDGE;
    options.Format    = GL_RGBA;
    options.PixFormat = GL_RGBA;
    options.Type      = GL_UNSIGNED_BYTE;

    this->CreateTexture(options, imgBuffer);

    if(imgBuffer) stbi_image_free(imgBuffer);
    
}

Texture::Texture(const unsigned char* imgBuffer, int width, int height, int bpp):
    m_width(width), m_height(height), m_bpp(bpp) 
{
        TextureOptions options;
    options.MinFilter = GL_LINEAR;
    options.MagFilter = GL_LINEAR;
    options.WrapS     = GL_CLAMP_TO_EDGE;
    options.WrapT     = GL_CLAMP_TO_EDGE;
    options.Format    = GL_RGBA;
    options.PixFormat = GL_RGBA;
    options.Type      = GL_UNSIGNED_BYTE;

    this->CreateTexture(options, (void*)imgBuffer);

}

Texture::Texture(int width, int height): m_width(width), m_height(height) {
    GLCall(glGenTextures(1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture() {
    if(m_rendererID) {
        GLCall(glDeleteTextures(1, &m_rendererID));
        m_rendererID = 0;
    }
}

void Texture::Bind(unsigned int slot /* = 0*/) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int Texture::texureId() { return m_rendererID; }

int Texture::width() const { return m_width; }

int Texture::height() const { return m_height; }

// Texture Storage
TextureStorage::TextureStorage() {}

TextureStorage::TextureStorage(int width, int height) {
    m_width = width;
    m_height = height;
    GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
    GLCall(glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTextureStorage2D(m_rendererID, 1, GL_RGBA32F, m_width, m_height));
    //GLCall(glBindImageTexture(0, m_rendererID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GLCall(glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}

void TextureStorage::Bind(unsigned int slot /* = 0*/) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
    GLCall(glBindImageTexture(slot, m_rendererID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F));
}

void TextureStorage::Unbind() const {
    GLCall(glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F));
}