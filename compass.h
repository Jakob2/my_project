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

private:
    int angle;
    float radius = 0.05;
    float comMidX = 0.825;
    float comMidY = 0.075;
    void calcAngle(std::vector<float> q, std::vector<float> m);
};

#endif // COMPASS_H
