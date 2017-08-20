#ifndef COMPASS_H
#define COMPASS_H

#include "general.h"
#include "world.h"
#include "vector.h"
#include "menumetrics.h"

class Compass : protected MenuMetrics
{
public:
    Compass();
    void drawCompass();
    void drawNeedle();
    bool panelCompass(std::vector<float> mouse);
    void hoverCompass(std::vector<float> mouse);
    void turnCamera(std::vector<float> q);
    float angle = 45;
    void calcCameraMoveUnits();
    std::vector<float> camMoveUnit = {World::cameraMove,World::cameraMove};

private:
    float radius = .1;
    /*float comMidX = .81;
    float comMidY = .125;*/
    float needleX, needleY;
    void calcAngle(std::vector<float> q);
    void calcNeedlePos();
    void turn();
};

#endif // COMPASS_H
