#ifndef MENU_H
#define MENU_H

#include "general.h"
#include "world.h"

class Menu
{
public:
    Menu();
    void background();

private:
    std::vector<float> backgroundColor = {.8,.8,.8};
    float menuWidth = 0.25;
    std::vector<float> menuX = {1-menuWidth,1};
    std::vector<float> menuY = {0,1};
};

#endif // MENU_H
