#include "vector.h"

/*Vector::Vector(){

}*/

std::vector<float> Vector::direction(std::vector<float> a, std::vector<float> b){
    std::vector<float> res;
    res[0] = b[0] - a[0];
    res[1] = b[1] - a[1];
    res[2] = b[2] - a[2];
    return res;
}

