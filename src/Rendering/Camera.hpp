#pragma once
#include <cml.h>
#include "Scene/Window.hpp"

class Camera {
public:
    Camera() = default;
    Camera(const Camera&) = delete;
    Camera operator=(const Camera&) = delete;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    const mat4& GetProjectionMatrix();
    const mat4 GetViewMatrix();
    Window* m_Window = nullptr;
protected:
    vec3 m_Position = vec3(0.0f, 0.0f, 2.0f);
    vec3 m_Orientation = vec3(0.0f, 0.0f, -1.0f);
    vec3 m_Up = vec3(0.0f, 1.0f, 0.0f);

    mat4 m_ProjectionMatrix;

    float m_Speed = 0.1f;
    float m_MouseSensitivity = 100.0f;

    bool m_FirstClick = true;
    bool m_Focused = false;

};

class PerspectiveCam: public Camera {
public:
    PerspectiveCam() = default;
    PerspectiveCam(float fov, float nearP, float farP, int width, int height);
    void OnUpdate();
    void OnRender();
private:
    float m_Fov;
    float m_Near;
    float m_Far;

    int m_Width;
    int m_Height;
};