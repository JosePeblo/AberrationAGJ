#include "Camera.hpp"

const mat4& Camera::GetProjectionMatrix() { return m_ProjectionMatrix; }

const mat4 Camera::GetViewMatrix()
{
    return cml::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

PerspectiveCam::PerspectiveCam(float fov, float nearPlane, float farPlane, int width, int height)
:m_Fov(fov), m_Near(nearPlane), m_Far(farPlane), m_Width(width), m_Height(height)
{
    m_ProjectionMatrix = cml::perspective(m_Fov, m_Width, m_Height, m_Near, m_Far);
}

void PerspectiveCam::OnUpdate()
{
    if(!m_Window) return;
    if(!m_Window->get_window()) return;

    auto wnd = m_Window->get_window();

    if(glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS){
        m_Position += m_Orientation * m_Speed;
    }
    if(glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS){
        m_Position += (m_Orientation * m_Speed).negate();
    }

    if(glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS){
        m_Position += cml::norm(cml::cross(m_Orientation, m_Up)).negate() * m_Speed;
    }

    if(glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS){
        m_Position += cml::norm(cml::cross(m_Orientation, m_Up)) * m_Speed;

    }

    if(glfwGetKey(wnd, GLFW_KEY_SPACE) == GLFW_PRESS){
        m_Position += m_Up * m_Speed;
    }

    if(glfwGetKey(wnd, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        m_Position += (m_Up * m_Speed).negate(); 
    }

    if(glfwGetMouseButton(wnd, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if(m_FirstClick)
        {
            glfwSetCursorPos(wnd, (m_Width / 2), (m_Height / 2));
            m_FirstClick = false;
            m_Focused = true;
        }
    }
    else if(glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_FirstClick = true;
        m_Focused = false;
    }
    if(m_Focused)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(wnd, &mouseX, &mouseY);

        float rotX = m_MouseSensitivity * (float)(mouseY - (m_Width / 2)) / m_Height;
        float rotY = m_MouseSensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;

        vec3 newOrientation = cml::rotate(m_Orientation, cml::radians(-rotX), cml::norm(cml::cross(m_Orientation, m_Up)));
        

        if(!(((cml::angle(newOrientation, m_Up)) <= cml::radians(5.0f)) || (cml::angle(newOrientation, cml::negate(m_Up)) <= cml::radians(5.0f))))
        {
            m_Orientation = newOrientation;
        }
        m_Orientation = cml::rotate(m_Orientation, cml::radians(-rotY), m_Up);

        glfwSetCursorPos(wnd, (m_Width / 2), (m_Height / 2));
    }
    if(glfwGetKey(wnd, GLFW_KEY_E) == GLFW_PRESS)
    {
        m_Up = cml::rotate(m_Up, cml::radians(2.f), cml::norm(m_Orientation));
    }

    if(glfwGetKey(wnd, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_Up = cml::rotate(m_Up, cml::radians(-2.f), cml::norm(m_Orientation));
    }

    if(glfwGetKey(wnd, GLFW_KEY_R) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } 
    if(glfwGetKey(wnd, GLFW_KEY_R) == GLFW_RELEASE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void PerspectiveCam::OnRender()
{

}
