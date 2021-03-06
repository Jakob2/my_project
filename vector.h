#ifndef VECTOR_H
#define VECTOR_H

#include "general.h"

class Vector
{
public:
    //Vector();
    static std::vector<float> numToVec(float x, float y, float z);
    static std::vector<float> direction(std::vector<float> a, std::vector<float> b);
    static float absolute(std::vector<float> in);
    static std::vector<float> normal(std::vector<float> a, std::vector<float> b);
    static std::vector<float> normalize(std::vector<float> a);
};

#endif // VECTOR_H
