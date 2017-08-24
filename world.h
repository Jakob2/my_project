#ifndef WORLD_H
#define WORLD_H

#include "general.h"

class World
{
public:
    World();

    static float pi;
    static int width;
    static int height;
    static float zoom;
    static float eyeX;
    static float eyeY;
    static float eyeZ;
    static int range;
    static int validPlace;
    static float x;
    static float z;
    static int areaOption;//???
    static float areaX;
    static float areaZ;
    static bool mousePressed;
    static float cameraMove;
    static std::vector<float> tile;
    static int hoverBuilding;
    static int hoverZoom;
    static int hoverCompass;
    static std::vector<float> hoverColor;
    static int buildingOption;
    static int map;
    static bool moveConstruct;
};

#endif // WORLD_H
