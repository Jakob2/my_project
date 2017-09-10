#include "world.h"

World::View World::view;
int World::range;
bool World::validPlace;
float World::x;
float World::z;
int World::areaOption;
float World::pi;
bool World::mousePressed;
float World::cameraMove;
std::vector<float> World::tile;
int World::hoverBuilding;
int World::hoverZoom;
int World::hoverCompass;
int World::buildingOption;
int World::map;
bool World::moveConstruct;
int World::constructId;
bool World::token;
int World::pickedColor;

World::World(){
    World::view.width = 800;
    World::view.height = 600;
    World::view.eyeX = 1;
    World::view.eyeY = 1;
    World::view.eyeZ = 1;
    World::view.zoom = .1;
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
    World::buildingOption = -1;
    World::map = 1;
    World::moveConstruct = false;
    World::constructId = -1;
    World::token = false;
}

