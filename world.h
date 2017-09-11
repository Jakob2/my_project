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
    static struct Tile{
        int map;
        int range;
        bool valid;
        float x;
        float z;
        std::vector<float> tile;
    }map;

    static int areaOption;//selectionColor ??
    static bool mousePressed;
    static float cameraMove;
    static int hoverBuilding;
    static int hoverZoom;
    static int hoverCompass;
    static int buildingOption;
    static bool moveConstruct;
    static int constructId;
    static bool token;
    static int pickedColor;
};

#endif // WORLD_H
