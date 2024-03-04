#pragma once
#include "cml.h"
#include <stdint.h>
#include <string>
#include <unordered_map>

enum UNIFORM_TYPE
{
    UNIFORM_NONE = -1,
    UNIFORM_BOOL, UNIFORM_INT, UNIFORM_UINT, UNIFORM_FLOAT, UNIFORM_DOUBLE,
    UNIFORM_BVEC2, UNIFORM_BVEC3, UNIFORM_BVEC4, 
    UNIFORM_IVEC2, UNIFORM_IVEC3, UNIFORM_IVEC4,
    UNIFORM_UVEC2, UNIFORM_UVEC3, UNIFORM_UVEC4,
    UNIFORM_VEC2, UNIFORM_VEC3, UNIFORM_VEC4,
    UNIFORM_DVEC2, UNIFORM_DVEC3, UNIFORM_DVEC4,
    UNIFORM_MAT2f,
    UNIFORM_MAT3f,
    UNIFORM_MAT4f
};

typedef int GLint;
struct Uniform
{
    GLint location = -1;
    UNIFORM_TYPE type = UNIFORM_NONE;
    void* data = nullptr;
};


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    public:
        Shader(){}
        Shader(const std::string& filePath);
        ~Shader();

        void Bind() const;
        void Unbind() const;
        void Reload();
        void SetNewPath(const std::string& filePath);
        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform2i(const std::string& name, ivec2& value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform2f(const std::string& name, const vec2& value);
        void SetUniform3f(const std::string& name, const vec3& value);
        void SetUniform4f(const std::string& name, const vec4& value);

        void SetUniformMat3f(const std::string& name, const mat3& matrix);
        void SetUniformMat4f(const std::string& name, const mat4& matrix);
        std::string GetPath() const { return m_filePath; }
        std::unordered_map<std::string, Uniform>& GetUniformCache() { return m_uniformLocationCache; }

    protected:
        std::string m_filePath;
        unsigned int m_rendererID;
        mutable std::unordered_map<std::string, Uniform> m_uniformLocationCache;

        ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CreateShader(const ShaderProgramSource& source);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        GLint GetUniformLocation(const std::string& name) const;
};

class ComputeShader : public Shader {
    public:
    ComputeShader(const std::string& filepath);
    ~ComputeShader()
    {
        // Parent destructor deletes the program and uniforms
    }
    void Dispatch(uint32_t groups_x, uint32_t groups_y, uint32_t groups_z) const;
    void Reload();
    private:
    std::string ParseShader(const std::string& filepath);
    uint32_t CreateShader(const std::string& source);
    uint32_t CompileShader(const std::string& source);
    

        // unsigned int CompileShader(std::string& src);
};
