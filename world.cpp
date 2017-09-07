#include "world.h"

int World::width;
int World::height;
float World::zoom;
float World::eyeX;
float World::eyeY;
float World::eyeZ;
int World::range;
bool World::validPlace;
float World::x;
float World::z;
int World::areaOption;
float World::areaX;
float World::areaZ;
float World::pi;
bool World::mousePressed;
float World::cameraMove;
std::vector<float> World::tile;
int World::hoverBuilding;
int World::hoverZoom;
int World::hoverCompass;
std::vector<float> World::hoverColor;
int World::buildingOption;
int World::map;
bool World::moveConstruct;
int World::constructId;
bool World::token;

World::World(){
    //World::width = 701;
    //World::height = 381;
    World::width = 800;
    World::height = 600;
    World::zoom = 0.2;
    World::eyeX = 1;
    World::eyeY = 1;
    World::eyeZ = 1;
    World::range = 10;
    World::x = 0;
    World::z = 0;
    World::areaOption = 0;
    World::pi = 3.14159265;
    World::mousePressed = false;
    World::cameraMove = 0.5;
    World::tile = {0,0,0,0,0,0};
    World::hoverBuilding = -1;
    World::hoverZoom = -1;
    World::hoverCompass = -1;
    World::hoverColor = {.5,.5,0}; //only used in gui class, refactor it ...
    World::buildingOption = -1;
    World::map = 1;
    World::moveConstruct = false;
    World::constructId = -1;
    World::token = false;
}

