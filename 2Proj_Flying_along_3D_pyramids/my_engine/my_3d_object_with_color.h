#include <vector>
#include "my_3d_xyz.h"

class My3D_ObjectWithColor
{
    // openGL
    public: void RenderWithColor();
    public: void AddPointWithColor(XYZ position, RGBA color);
    public: void SetDrawMode(int drawMode);
    public: void RemoveAllPoints();

    // points
    protected: int m_DrawMode = 0;
    protected: std::vector<XYZ_RGBA> m_arrPositionWithColor;
};

class My3D_PyramidWithColor : public My3D_ObjectWithColor
{
    public: My3D_PyramidWithColor(XYZ pointCenter, float sideSize, RGBA colorForTopPoints, RGBA colorForBottomColors);
};

class My3D_RectWithColor : public My3D_ObjectWithColor
{
    public: My3D_RectWithColor(XYZ pointCenter, float xSide, float zSize, RGBA color);
};