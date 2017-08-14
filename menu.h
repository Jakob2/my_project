#ifndef MENU_H
#define MENU_H

#include "general.h"
#include "world.h"
#include "compass.h"

class Menu : public Compass
{
public:
    Menu();
    void drawMenu();

private:
    void background();
    std::vector<float> backgroundColor = {.8,.8,.8};
    float menuWidth = 0.25;
    std::vector<float> menuX = {1-menuWidth,1};
    std::vector<float> menuY = {0,1};
};

#endif // MENU_H
