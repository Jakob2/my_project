#ifndef BUILDING_H
#define BUILDING_H

#include "general.h"
#include "world.h"
#include "menumetrics.h"

class Building : protected MenuMetrics
{
public:
    Building();

    void options();
    void hoverBuildings(std::vector<float> mouse);
    bool panelBuildings(std::vector<float> mouse);
    void onBuildings(QMouseEvent *event);

private:
    /*float f = .01;
    std::vector<float> margin = {.81, .89};
    void setMargin();
    std::vector<float> vertice = {.05, .1};*/
};

#endif // BUILDING_H
