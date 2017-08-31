#ifndef GUI_H
#define GUI_H

#include "general.h"
#include "world.h"
#include "db.h"

class Gui : public Db
{
public:
    Gui();

    void drawMenu();
    std::vector<float> mouseToMenuGrid(int mouseX, int mouseY);
    bool panelMenu(float mouseX, float mouseY);

    void options();
    void uniqueColoredOptions();
    void hoverBuildings(std::vector<float> mouse);
    bool panelBuildings(std::vector<float> mouse);
    void onBuildings(QMouseEvent *event);

    void selectIcons();
    void drawIcon();
    std::vector<std::vector<int>> icons;

    void zoom();
    void drawZoom();
    bool panelZoom(std::vector<float> mouse);
    void hoverZoom(std::vector<float> mouse);
    void drawCompass();
    void drawNeedle();

    float angle = 45;
    std::vector<float> camMoveUnit = {World::cameraMove,World::cameraMove};
    bool panelCompass(std::vector<float> mouse);
    void hoverCompass(std::vector<float> mouse);
    void turnCamera(std::vector<float> q);
    void calcCameraMoveUnits();

private:
    void background();
    std::vector<float> backgroundColor = {.8,.8,.8};
    float menuWidth = .25;
    std::vector<float> menuX = {1-menuWidth,1};
    std::vector<float> menuY = {0,1};

    std::vector<int> buildingId = {1,0,3,7,999,999};

    void setIcons();

    void plus();
    void minus();

    float radius = .1;
    float needleX, needleY;
    void calcAngle(std::vector<float> q);
    void calcNeedlePos();
    void turn();

    //building
    float f = .01;
    std::vector<float> margin = {.81, .89};
    void setMargin();
    std::vector<float> vertice = {.05, .1};
    //compass
    float comMidX = .81;
    float comMidY = .125;
    //icon
    int numIcons = 6;
    std::vector<float> iconPos = {.76,.79, .861,.79, .76,.59, .861,.59, .76,.39, .861,.39};
    void setIconPos();
    //zoom
    //float f = .01;
    float weight = .25;
    std::vector<float> mid = {.885,.125, .935,.125};
    std::vector<float> v = {.025, .05};

};

#endif // GUI_H
