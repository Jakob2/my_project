#ifndef MENUMETRICS_H
#define MENUMETRICS_H

#include "general.h"

class MenuMetrics
{
public:
    MenuMetrics();

protected:
    //building
    float f = .01;
    std::vector<float> margin = {.81, .89};
    void setMargin();
    std::vector<float> vertice = {.05, .1};
    //compass
    float comMidX = .81;
    float comMidY = .125;
    //icon
    int numIcons = 6;
    std::vector<float> iconPos = {.76,.79, .861,.79, .76,.59, .861,.59, .76,.39, .861,.39};
    void setIconPos();
    //zoom
    //float f = .01;
    float weight = .25;
    std::vector<float> mid = {.885,.125, .935,.125};
    std::vector<float> v = {.025, .05};
};

#endif // MENUMETRICS_H
