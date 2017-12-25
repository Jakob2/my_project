#ifndef HOUSE_H
#define HOUSE_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "shape.h"

class House
{
public:
    House();
    House(int name);

    void selectHouse(int name, int map);
    void renderHouse(float xPos, float zPos);

private:
    int vectorMainSize = 8;
    int vectorSubSize = 3;
    void initPolygon(int size);
    std::vector<std::vector<std::vector<float>>> polygon;
    void corpus(int i, float x, float y, float z, float xPos, float zPos);
};

#endif // HOUSE_H
