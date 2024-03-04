#include "my_3d_object_with_color.h"
#include "../../glut_lib/glut.h"

void My3D_ObjectWithColor::RenderWithColor()
{
    int countOfPointsToDraw = m_arrPositionWithColor.size();

    // point (x,y,z)
    glVertexPointer(3, // it is count of fields: x,y,z
                    GL_FLOAT,
                    sizeof(XYZ_RGBA),
                    (GLvoid*)m_arrPositionWithColor.data()
    );

    // color (r,g,b,alpha)
    glColorPointer(4, // it is count of fields: red,green,blue, alpha
                   GL_FLOAT,
                   sizeof(XYZ_RGBA),
                   (GLvoid*) ((char*)m_arrPositionWithColor.data() + offsetof(XYZ_RGBA, ColorRGBA)) // shift to color
    );

    glDrawArrays(m_DrawMode, 0 /*first index to draw*/, countOfPointsToDraw);
}

void My3D_ObjectWithColor::AddPointWithColor(XYZ position, RGBA color)
{
    m_arrPositionWithColor.push_back(XYZ_RGBA(position, color));
}

void My3D_ObjectWithColor::SetDrawMode(int drawMode)
{
    m_DrawMode = drawMode;
}

void My3D_ObjectWithColor::RemoveAllPoints()
{
    m_arrPositionWithColor.clear();
}


// Pyramid
My3D_PyramidWithColor::My3D_PyramidWithColor(XYZ pointCenter, float sideSize, RGBA colorForTopPoint, RGBA colorForBottomPoints)
{
    RemoveAllPoints();

    // top point
    AddPointWithColor(XYZ(pointCenter.X, pointCenter.Y, pointCenter.Z), colorForTopPoint);

    // bottom points
    //      .
    //    .   .
    //      .
    AddPointWithColor(XYZ(pointCenter.X-sideSize/2.f, pointCenter.Y-sideSize/2.f, pointCenter.Z+sideSize/2.f), colorForBottomPoints);
    AddPointWithColor(XYZ(pointCenter.X+sideSize/2.f, pointCenter.Y-sideSize/2.f, pointCenter.Z+sideSize/2.f), colorForBottomPoints);
    AddPointWithColor(XYZ(pointCenter.X+sideSize/2.f, pointCenter.Y-sideSize/2.f, pointCenter.Z-sideSize/2.f), colorForBottomPoints);
    AddPointWithColor(XYZ(pointCenter.X-sideSize/2.f, pointCenter.Y-sideSize/2.f, pointCenter.Z-sideSize/2.f), colorForBottomPoints);
    AddPointWithColor(XYZ(pointCenter.X-sideSize/2.f, pointCenter.Y-sideSize/2.f, pointCenter.Z+sideSize/2.f), colorForBottomPoints);

    // draw mode
    SetDrawMode(GL_TRIANGLE_FAN);
}

// Rectangle
My3D_RectWithColor::My3D_RectWithColor(XYZ pointCenter, float xSide, float zSize, RGBA color)
{
    RemoveAllPoints();

    // points
    //    .  .
    //    .  .
    AddPointWithColor(XYZ(pointCenter.X-xSide/2.f, pointCenter.Y, pointCenter.Z+zSize/2.f), color);
    AddPointWithColor(XYZ(pointCenter.X+xSide/2.f, pointCenter.Y, pointCenter.Z+zSize/2.f), color);
    AddPointWithColor(XYZ(pointCenter.X-xSide/2.f, pointCenter.Y, pointCenter.Z-zSize/2.f), color);
    AddPointWithColor(XYZ(pointCenter.X+xSide/2.f, pointCenter.Y, pointCenter.Z-zSize/2.f), color);

    // draw mode
    SetDrawMode(GL_TRIANGLE_STRIP);
}