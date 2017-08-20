#include "menu.h"

Menu::Menu(){

}

void Menu::drawMenu(){
    drawIcon();
    options();
    drawZoom();
    drawNeedle();
    drawCompass();
    background();
}

std::vector<float> Menu::mouseToMenuGrid(int mouseX, int mouseY){
    std::vector<float> res;
    res.resize(3);
    res[0] = (float)mouseX/World::width;
    res[1] = 1-(float)mouseY/World::height;
    res[2] = 0;
    //std::cout<<res[0]<<"-"<<res[1]<<"-"<<res[2]<<std::endl;
    return res;
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
