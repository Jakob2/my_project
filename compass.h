#ifndef COMPASS_H
#define COMPASS_H

#include "general.h"
#include "world.h"
#include "vector.h"

class Compass
{
public:
    Compass();
    void drawCompass();
    void drawNeedle();
    bool panelCompass(std::vector<float> in);
    void turnCamera(std::vector<float> q);
    float comMidX = 0.825;
    float comMidY = 0.125;

private:
    float angle;
    float radius = 0.1;
    float needleX, needleY;
    void calcAngle(std::vector<float> q);
    void calcNeedlePos();
    void turn();
};

#endif // COMPASS_H
