#include "world.h"

World::View World::view;
World::Tile World::map;

int World::areaOption;
float World::pi;
bool World::mousePressed;
float World::cameraMove;
int World::hoverBuilding;
int World::hoverZoom;
int World::hoverCompass;
int World::buildingOption;
bool World::moveConstruct;
int World::constructId;
bool World::token;
int World::pickedColor;

World::World(){
    World::pi = 3.14159265;
    World::view.width = 800;
    World::view.height = 600;
    World::view.eyeX = 1;
    World::view.eyeY = 1;
    World::view.eyeZ = 1;
    World::view.zoom = .1;

    World::map.map = 1;
    World::map.range = 10;
    World::map.x = 0;
    World::map.z = 0;
    World::map.valid = false;
    World::map.tile = {0,0, 0,0, 0,0};

    World::areaOption = 0;
    World::mousePressed = false;
    World::cameraMove = 0.5;
    World::hoverBuilding = -1;
    World::hoverZoom = -1;
    World::hoverCompass = -1;
    World::buildingOption = -1;
    World::moveConstruct = false;
    World::constructId = -1;
    World::token = false;
}

