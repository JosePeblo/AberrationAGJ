#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>

#include <cml.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
    #include <commdlg.h>
#endif

void glfw_error_callback(int error, const char* description);

class Window
{
    private:
        GLFWwindow* m_window = nullptr;
        bool        m_windowOk = true;
        const char* m_glsl_version = "#version 460";
        ivec2       m_dimentions;
        const char* m_tile;

        // FPS counter
        double      m_prevTime = 0.0;
        double      m_crntTime = 0.0;
        double      m_timeDiff = 0.0;
        uint32_t    m_counter  = 0;

    public:

    Window() = default;
    Window(int width, int height, const char* title);

    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) noexcept;

    ~Window();

    void pollEvents();

    int windowShouldClose();

    void swapBuffers();

    void clear();

    bool ok();

    ivec2 GetDims() const;

    GLFWwindow* get_window();

    const char* getGlslVersion();

    std::string openFile(const char* filter);

    std::string saveFile(const char* filter);
};
