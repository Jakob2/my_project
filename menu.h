#ifndef MENU_H
#define MENU_H

#include "general.h"
#include "world.h"
#include "compass.h"
#include "building.h"
#include "zoom.h"

class Menu : public Compass, public Building, public Zoom
{
public:
    Menu();
    void drawMenu();
    std::vector<float> mouseToMenuGrid(int mouseX, int mouseY);

private:
    void background();
    std::vector<float> backgroundColor = {.8,.8,.8};
    float menuWidth = .25;
    std::vector<float> menuX = {1-menuWidth,1};
    std::vector<float> menuY = {0,1};
};

#endif // MENU_H
