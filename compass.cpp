#include "compass.h"

Compass::Compass(){

}

void Compass::drawCompass(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    //for(float i=0; i<2*World::pi; i+=World::pi/12)
    for(int i=0; i<360; i++)
        glVertex2f(comMidX+(cos(i)*radius)/2, comMidY+(sin(i)*radius));
    glEnd();
}

void Compass::calcAngle(std::vector<float> q, std::vector<float> m){
    std::vector<float> v;
    v = Vector::direction(m,q);
    angle = pow((v[0]/radius),-1);
}

