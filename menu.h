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
    std::vector<float> menuX;
    std::vector<float> menuY;
    float menuWidth = 0.25;
};


#endif // MENU_H
