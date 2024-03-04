#include "my_3d_camera.h"
#include "../../glut_lib/glut.h"

// glm
#include "../../glm-0.9.9.8/glm/gtc/type_ptr.hpp"

void My3D_Camera::Init(float zNear, float zFar, XYZ cameraPosition, XYZ cameraLookAt)
{
    // init Perspective
    m_Perspective_Fovy = 45.0f; // standard
    m_Perspective_Aspect = 1.0f; // standard
    m_Perspective_zNear = zNear;
    m_Perspective_zFar = zFar;

    // init camera
    m_CameraPosition = cameraPosition;
    m_CameraLookAt = cameraLookAt;
    m_CameraUp = {0, 1, 0}; // standard
}

void My3D_Camera::ApplyCameraPosition_to_OpenGLMatrix()
{
    // Camera (model view matrix)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    auto viewMarice_Camera = glm::lookAt(
            glm::vec3(m_CameraPosition.X, m_CameraPosition.Y, m_CameraPosition.Z),
            glm::vec3(m_CameraLookAt.X, m_CameraLookAt.Y, m_CameraLookAt.Z),
            glm::vec3(m_CameraUp.X, m_CameraUp.Y, m_CameraUp.Z)
    );
    glLoadMatrixf(glm::value_ptr(viewMarice_Camera));

    // Perspective (model view matrix)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto perspectiveMarice_Camera = glm::perspective(m_Perspective_Fovy, m_Perspective_Aspect, m_Perspective_zNear, m_Perspective_zFar);
    glLoadMatrixf(glm::value_ptr(perspectiveMarice_Camera));
}

void My3D_Camera::MoveCamera(float xOffset, float yOffset, float zOffset)
{
    m_CameraPosition.X += xOffset;
    m_CameraLookAt.X += xOffset;

    m_CameraPosition.Y += yOffset;
    m_CameraLookAt.Y += yOffset;

    m_CameraPosition.Z += zOffset;
    m_CameraLookAt.Z += zOffset;
}