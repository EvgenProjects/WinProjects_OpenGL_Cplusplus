#include "my_3d_xyz.h"

class My3D_Camera
{
    // openGL
    public: void Init(float zNear, float zFar, XYZ cameraPosition, XYZ cameraLookAt);
    public: void ApplyCameraPosition_to_OpenGLMatrix();
    public: XYZ GetCameraPosition() {return m_CameraPosition;}
    public: void MoveCamera(float xOffset, float yOffset, float zOffset);

    // camera
    protected: XYZ m_CameraPosition;
    protected: XYZ m_CameraLookAt;
    protected: XYZ m_CameraUp;

    // perspective
    protected: float m_Perspective_Fovy;
    protected: float m_Perspective_Aspect;
    protected: float m_Perspective_zNear;
    protected: float m_Perspective_zFar;
};
