#include "vector.h"

/*Vector::Vector(){

}*/

std::vector<float> Vector::numToVec(float x, float y, float z){
    std::vector<float> res;
    res.resize(2);
    res[0] = x;
    res[1] = y;
    res[2] = z;
    //std::cout<<res[0]<<"-"<<res[1]<<"-"<<res[2]<<std::endl;
    return res;
}

std::vector<float> Vector::direction(std::vector<float> a, std::vector<float> b){
    std::vector<float> res;
    res.resize(3);
    res[0] = b[0] - a[0];
    res[1] = b[1] - a[1];
    res[2] = b[2] - a[2];
    return res;
}

float Vector::absolute(std::vector<float> in){
    float res;
    res = sqrt((pow(in[0],2)+pow(in[1],2)+pow(in[2],2)));
    return res;
}

std::vector<float> Vector::normal(std::vector<float> a, std::vector<float> b){
    std::vector<float> out;
    out.resize(3);
    float x,y,z;
    //x = a[1]*b[2] - a[2]*b[1];
    x = a[2]*b[1] - a[1]*b[2];
    y = a[2]*b[0] - a[0]*b[2];
    z = a[0]*b[1] - a[1]*b[0];
    return out = {x,y,z};
}

std::vector<float> Vector::normalize(std::vector<float> a){
    std::vector<float> out;
    out.resize(3);
    float x,y,z, abs;
    abs =  Vector::absolute(a);
    x = a[0] / abs;
    y = a[1] / abs;
    z = a[2] / abs;
    return out = {x,y,z};
}

