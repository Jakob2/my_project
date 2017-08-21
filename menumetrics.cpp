#include "menumetrics.h"

MenuMetrics::MenuMetrics(){
    setMargin();
    setIconPos();
}

void MenuMetrics::setMargin(){
    margin[0] = 0.75 + vertice[0] + 0.01;
    margin[1] = 1 - vertice[1] - 0.01;
}

void MenuMetrics::setIconPos(){
    iconPos[0] = margin[0] - vertice[0];
    iconPos[1] = margin[1] - vertice[1];
    iconPos[2] = margin[0] + vertice[0] + f;
    iconPos[3] = margin[1] - vertice[1];
    iconPos[4] = margin[0] - vertice[0];
    iconPos[5] = margin[1] - vertice[1]*3;
    iconPos[6] = margin[0] + vertice[0] + f;
    iconPos[7] = margin[1] - vertice[1]*3;
    iconPos[8] = margin[0] - vertice[0];
    iconPos[9] = margin[1] - vertice[1]*5;
    iconPos[10] = margin[0] + vertice[0] + f;
    iconPos[11] = margin[1] - vertice[1]*5;
}
