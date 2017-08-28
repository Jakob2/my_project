#ifndef SHAPES_H
#define SHAPES_H

#include "general.h"
#include "world.h"

class Shape
{
public:
    Shape();

    void flatCube(float depth, int i, int j, float x, float y, float z);// float r, float g, float b);
    void corpus(std::vector<std::vector<std::vector<float> > > &construct, int i, float x, float y, float z, float xPos, float zPos);
    void wireToken(std::vector<std::vector<std::vector<float>>> token, float clip, int x, int z, float offX, float offZ, std::vector<std::vector<std::vector<int>>> &mapTiles);
    void top(int i, int j, float x, float y, float z);

private:    
    void left(float depth, int i, int j, float x, float y, float z);
    void back(float depth, int i, int j, float x, float y, float z);
    void right(float depth, int i, int j, float x, float y, float z);
    void front(float depth, int i, int j, float x, float y, float z);
};

#endif // SHAPES_H
