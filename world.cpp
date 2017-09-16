#include "world.h"

float World::pi;
World::View World::view;
World::Tile World::map;
World::Gui World::gui;
World::Mouse World::mouse;

World::World(){
    World::pi = 3.14159265;

    World::mouse.pressed = false;
    World::mouse.pickedColor = 0;

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
    World::map.constructId = -1;
    World::map.token = false;

    World::gui.hoverBuilding = -1;
    World::gui.hoverZoom = -1;
    World::gui.hoverCompass = -1;
    World::gui.buildingOption = -1;
    World::gui.areaOption = 0;
}
