#include "menu.h"

Menu::Menu(){
    menuX = {1-menuWidth,1};
    menuY = {0,1};
}

void Menu::background(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(menuX[0],menuY[0]);
        glVertex2f(menuX[0],menuY[1]);
        glVertex2f(menuX[1],menuY[1]);
        glVertex2f(menuX[1],menuY[0]);
    glEnd();
}

