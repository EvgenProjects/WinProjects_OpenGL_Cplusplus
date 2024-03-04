#pragma once

struct XYZ
{
    float X;
    float Y;
    float Z;

    XYZ(float x=0, float y=0, float z=0) {X=x, Y=y, Z=z;}
};

struct RGBA
{
    float Red;   // [0...1]
    float Green; // [0...1]
    float Blue;  // [0...1]
    float Alpha; // [0...1]

    // by default white color (1, 1, 1, 1)
    RGBA(float r=1, float g=1, float b=1, float a=1) {Red=r, Green=g, Blue=b; Alpha=a;}
};

struct XYZ_RGBA
{
    XYZ PositionXYZ;
    RGBA ColorRGBA;

    XYZ_RGBA(XYZ position=XYZ(), RGBA color=RGBA() ) {PositionXYZ=position, ColorRGBA=color;}
};
