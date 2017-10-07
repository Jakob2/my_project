#ifndef SHAPES_H
#define SHAPES_H

#include "general.h"
#include "world.h"
#include "vector.h"

class Shape
{
public:
    //Shape();

    static void flatCube(float depth, int i, int j, float x, float y, float z);// float r, float g, float b);
    static void corpus(std::vector<std::vector<std::vector<float> > > &construct, int i, float x, float y, float z, float xPos, float zPos);
    //static void wireToken(std::vector<std::vector<std::vector<float>>> token, float clip, int x, int z, float offX, float offZ, std::vector<std::vector<std::vector<int>>> &mapTiles);
    static void top(int i, int j, float x, float y, float z);

private:
    static void left(float depth, int i, int j, float x, float y, float z);
    static void back(float depth, int i, int j, float x, float y, float z);
    static void right(float depth, int i, int j, float x, float y, float z);
    static void front(float depth, int i, int j, float x, float y, float z);
};

#endif // SHAPES_H
