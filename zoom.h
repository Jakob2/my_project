#ifndef ZOOM_H
#define ZOOM_H

#include "general.h"
#include "world.h"
#include "menumetrics.h"

class Zoom : protected MenuMetrics
{
public:
    Zoom();
    void zoom();
    void drawZoom();
    bool panelZoom(std::vector<float> mouse);
    void hoverZoom(std::vector<float> mouse);

private:
    /*float f = .01;
    float weight = .25;
    std::vector<float> mid = {.885,.125, .935,.125};
    std::vector<float> v = {.025, .05};*/
    void plus();
    void minus();
};

#endif // ZOOM_H
