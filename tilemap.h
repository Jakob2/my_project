#ifndef TILEMAP_H
#define TILEMAP_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "shape.h"

class Tilemap : public Db, public Shape
{
public:
    Tilemap();

    void selectMapTiles();
    static std::vector<std::vector<std::vector<int>>> mapTiles;
    void ground(float x, float z, std::vector<std::vector<std::vector<int>>> &mapTiles);

private:
    const float clip = 0.5;
    std::vector<float> select = {.9,.9,.9};
    std::vector<float> color = {0,0,0};
    std::vector<float> grass = {0,1,0};
    std::vector<float> water = {0,0,1};
    std::vector<float> desert = {.4,.4,.4};
    void setMapTiles();
    float sink(int type);
    void selectionColor(int i, int j, int ii, int jj, int clr);
    void area(int i, int ii, int j, int jj, int clr);
    void single(int i, int ii, int j, int jj, int clr);
    void parseColor(int c);
};

#endif // TILEMAP_H
