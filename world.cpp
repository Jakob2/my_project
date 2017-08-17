#include "world.h"

int World::width;
int World::height;
float World::zoom;
float World::eyeX;
float World::eyeY;
float World::eyeZ;
int World::range;
int World::validPlace;
float World::x;
float World::z;
int World::option;
float World::intersectionX;
float World::intersectionZ;
float World::areaX;
float World::areaZ;
float World::pi;
bool World::mousePressed;
float World::cameraMove;

World::World(){
    World::width = 701;
    World::height = 381;
    World::zoom = 0.2;
    World::eyeX = 1;
    World::eyeY = 1;
    World::eyeZ = 1;
    World::range = 10;
    World::x = 0;
    World::z = 0;
    World::option = 0;
    World::pi = 3.14159265;
    World::mousePressed = false;
    World::cameraMove = 0.5;
}

