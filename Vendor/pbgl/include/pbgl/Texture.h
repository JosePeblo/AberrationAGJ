#pragma once
#include <glad/glad.h>

struct TextureOptions {
    GLint MinFilter = GL_NEAREST;
    GLint MagFilter = GL_NEAREST;
    GLint WrapS     = GL_CLAMP_TO_EDGE;
    GLint WrapT     = GL_CLAMP_TO_EDGE;
    GLint MipLevels = 0;
    GLint Format    = GL_RGBA;
    GLint PixFormat = GL_RGBA;
    GLenum Type     = GL_UNSIGNED_BYTE;
};

class Texture {
public:
    Texture();
    // Create from image path
    Texture(const char* filePath, int flip = 1);
    // Create forome pre-loaded image
    Texture(const unsigned char* imgBuffer, int width, int height, int bpp);
    // Create empty texture with default parameters
    Texture(int width, int height);

    // Create texture with custom parameters
    Texture(int width, int height, const TextureOptions& options);
    
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) noexcept;

    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    int width() const;
    int height() const;
    unsigned int texureId();

protected:
    unsigned int m_rendererID = 0;
    int m_width = 0;
    int m_height = 0;
    int m_bpp = 0;

    void CreateTexture(const TextureOptions& options, void* ptr = nullptr);

friend class FrameBuffer;
};

class TextureStorage: public Texture {
public:
    TextureStorage();
    TextureStorage(int width, int height);
    ~TextureStorage() {};
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};
