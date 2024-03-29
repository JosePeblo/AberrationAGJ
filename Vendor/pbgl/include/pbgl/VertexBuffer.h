#pragma once

class VertexBuffer
{
    public:
        VertexBuffer(){ m_rendererID = -1; }
        VertexBuffer(const void* data, unsigned int size);
        VertexBuffer(const VertexBuffer& that) = delete;
        VertexBuffer& operator=(const VertexBuffer& that) = delete;
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_rendererID;
};
