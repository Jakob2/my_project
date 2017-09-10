#ifndef WORLD_H
#define WORLD_H

#include "general.h"

class World
{
public:
    World();

    static float pi;
    static struct View{
        int width;
        int height;
        float eyeX;
        float eyeY;
        float eyeZ;
        float zoom;
    }view;

    static int range;
    static bool validPlace;
    static float x;
    static float z;
    static int areaOption;//selectionColor ??
    static bool mousePressed;
    static float cameraMove;
    static std::vector<float> tile;
    static int hoverBuilding;
    static int hoverZoom;
    static int hoverCompass;
    static int buildingOption;
    static int map;
    static bool moveConstruct;
    static int constructId;
    static bool token;
    static int pickedColor;
};

#endif // WORLD_H
