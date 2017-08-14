#include "menu.h"

Menu::Menu(){

}

void Menu::drawMenu(){
    drawNeedle();
    drawCompass();
    background();
}

void Menu::background(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(backgroundColor[0],backgroundColor[1],backgroundColor[2]);
    glBegin(GL_POLYGON);
        glVertex2f(menuX[0],menuY[0]);
        glVertex2f(menuX[0],menuY[1]);
        glVertex2f(menuX[1],menuY[1]);
        glVertex2f(menuX[1],menuY[0]);
        glEnd();
}
