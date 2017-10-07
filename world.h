#ifndef WORLD_H
#define WORLD_H

#include "general.h"

class World
{
public:
    World();

    static float candleHeight;

    static float pi;

    static struct Mouse{
        int pickedColor;
        bool pressed;
    }mouse;

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
        int constructId;
        bool token;
    }map;

    static struct Gui{
        int hoverBuilding;
        int hoverZoom;
        int hoverCompass;
        int buildingOption;
        int areaOption;
        bool selected;
    }gui;
};

#endif // WORLD_H
