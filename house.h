#ifndef HOUSE_H
#define HOUSE_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "shape.h"

class House
{
public:
    House(int id);
    void renderHouse(float xPos, float zPos);

private:
    int vectorMainSize = 8;
    int vectorSubSize = 3;
    void initPolygon(int size);
    void selectHouse(int id, int map);
    std::vector<std::vector<std::vector<float>>> polygon;
    void corpus(int i, float x, float y, float z, float xPos, float zPos);
    int sizeOfHousePolygon(int id);
};

class NewHouse
{
public:
    NewHouse(int name);
    void renderNewHouse(float xPos, float zPos);
    void saveNewHouse(QString map, QString name, QString x, QString z);

private:
    int vectorMainSize = 8;
    int vectorSubSize = 3;
    void initPolygon(int size);
    std::vector<std::vector<std::vector<float>>> polygon;
    void selectHouseByName(int name);
    void corpus(int i, float x, float y, float z, float xPos, float zPos);
    int sizeOfHousePolygon(int name);
    QString id();
};

#endif // HOUSE_H
