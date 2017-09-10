#ifndef MOUSERAY_H
#define MOUSERAY_H

#include "general.h"
#include "world.h"
#include "vector.h"

class Mouseray
{
public:
    Mouseray();
    void calculateGLCoords(int x, int y);
    std::vector<float> calculateGLCoordsTest(int x, int y);
    bool panelWorld(std::vector<float> in);
    void crossfade();
    bool checkIfOnTilemap(int x, int y);
    //bool hoverGui(int x, int y);

    void readPixelColor(int x, int y);

    std::vector<float> testIntersection = {0,0,0};
private:
    GLint viewport[4];// Where The Viewport Values Will Be Stored
    GLdouble modelview[16];// Where The 16 Doubles Of The Modelview Matrix Are To Be Stored
    GLdouble projection[16];// Where The 16 Doubles Of The Projection Matrix Are To Be Stored
    std::vector<int> mouse;// Stores The X And Y Coords For The Current Mouse Position
    GLfloat winX, winY, winZ;// Holds Our X, Y and Z Coordinates
    GLdouble posX, posY, posZ;
    //std::vector<float> e = {World::eyeX, World::eyeY, World::eyeZ};
    std::vector<float> e = {World::view.eyeX, World::view.eyeY, World::view.eyeZ};
    std::vector<float> p = {0,0,0};
    void intersect(std::vector<float> in);
    std::vector<float> intersectTest(std::vector<float> in);

    int pickedId;
};

#endif // MOUSERAY_H
