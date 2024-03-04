#include "Window.hpp"
#include <pbgl/pbgl.h>

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Window::Window(int width, int height, const char* title): 
    m_dimentions({ width, height }), m_tile(title){
    glfwSetErrorCallback(glfw_error_callback);

    /* Initialize glfw */
    if (!glfwInit())
    {
        m_windowOk = false;
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(m_dimentions.x, m_dimentions.y, m_tile, NULL, NULL);

    if (!m_window)
    {
        m_windowOk = false;
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // TODO: Enable graphics api abstraction
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        puts("Failed to initialize OpenGL context\n");
        m_windowOk = false;
        return;
    }

    // m_glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);    

}

Window::~Window()
{
    if(m_window){
        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_windowOk = false;
    }
}

Window& Window::operator=(Window&& that) noexcept 
{
    m_window = that.m_window;
    m_windowOk = that.m_windowOk;
    m_dimentions.x = that.m_dimentions.x;
    m_dimentions.y = that.m_dimentions.y;

    m_prevTime = that.m_prevTime;
    m_crntTime = that.m_crntTime;
    m_timeDiff = that.m_timeDiff;
    m_counter  = that.m_counter;

    that.m_window = nullptr; 
    return *this;
}


void Window::pollEvents() 
{ 
    /* Poll for and process events */
    glfwPollEvents();
}

void Window::clear()
{
    // TODO: abstract for different graphics api
    GLCall(glClearColor(0.24f, 0.24f, 0.24f, 1.f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

int Window::windowShouldClose() { return glfwWindowShouldClose(m_window); }

void Window::swapBuffers(){
    // m_crntTime = glfwGetTime();
    // m_timeDiff = m_crntTime - m_prevTime;
    // m_counter++;
    // if(m_timeDiff >= 1.0 / 30.0)
    // {
    //     std::string FPS = std::to_string((1.0 / m_timeDiff) * m_counter);
    //     std::string ms  = std::to_string((m_timeDiff / m_counter) * 1000);
    //     std::string title = FPS + "fps / " + ms + "ms";
    //     glfwSetWindowTitle(m_window, title.c_str());
    // }

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);
}

bool Window::ok() { return m_windowOk; }

GLFWwindow* Window::get_window() { return m_window; }

const char* Window::getGlslVersion() { return m_glsl_version; }

ivec2 Window::GetDims() const { return m_dimentions; }


std::string Window::openFile(const char* filter) {
    #ifdef _WIN32
    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(m_window);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if(GetOpenFileNameA(&ofn) == TRUE)
    {
        return ofn.lpstrFile;
    }
    return std::string();

    #endif
    //TODO: implementation for other platforms
}

std::string Window::saveFile(const char* filter) {
    #ifdef _WIN32
    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = glfwGetWin32Window(m_window);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if(GetSaveFileNameA(&ofn) == TRUE)
    {
        return ofn.lpstrFile;
    }
    return std::string();

    #endif
    //TODO: implementation for other platforms
}


