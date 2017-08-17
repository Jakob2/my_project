#ifndef BUILDING_H
#define BUILDING_H

#include "general.h"
#include "world.h"

class Building
{
public:
    Building();

    void options();
    void hoverBuildings(std::vector<float> mouse);
    bool panelBuildings(std::vector<float> mouse);

private:
    float f = 0.01;
    std::vector<float> margin = {0.81, 0.89};
    void setMargin();
    std::vector<float> vertice = {0.05, 0.1};
};

#endif // BUILDING_H
