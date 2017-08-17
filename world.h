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
    static int option;//???
    static float intersectionX;//???
    static float intersectionZ;//???
    static float areaX;
    static float areaZ;
    static bool mousePressed;
    static float cameraMove;
    static std::vector<float> tile;
};

#endif // WORLD_H
