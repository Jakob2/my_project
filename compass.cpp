#include "compass.h"

Compass::Compass(){
    needleX = comMidX+radius/2;
    needleY = comMidY;
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

void Compass::drawNeedle(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(needleX-.005, needleY-.01);
        glVertex2f(needleX-.005, needleY+.01);
        glVertex2f(needleX+.005, needleY+.01);
        glVertex2f(needleX+.005, needleY-.01);
    glEnd();

}

bool Compass::panelCompass(std::vector<float> in){
    bool res = false;
    //std::cout<<comMidX-radius/2<<"-"<<comMidX+radius/2<<"/"<<comMidY-radius<<"-"<<comMidY+radius<<std::endl;
    //std::cout<<in[0]<<"//"<<in[1]<<std::endl;
    if(in[0]>comMidX-radius/2 && in[0]<comMidX+radius/2 && in[1]>comMidY-radius && in[1]<comMidY+radius) res = true;
    return res;
}

void Compass::turnCamera(std::vector<float> q){
    calcAngle(q);
    calcNeedlePos();
}

void Compass::calcAngle(std::vector<float> q){
    float x,y,s;
    x = (q[0] - comMidX) * 2;
    y = q[1] - comMidY;
    s = sqrt(pow(x,2)+pow(y,2));
    angle = asin(y/s) * (180.0/World::pi);
    if(x<0) angle = 180 - angle;
    if(angle<0) angle = 360 + angle;
    //angle = floor(angle);
    std::cout<<"angle "<<angle<<std::endl;
}

void Compass::calcNeedlePos(){
    needleX = (cos(angle*World::pi/180)*radius/2) + comMidX;
    needleY = (sin(angle*World::pi/180)*radius) + comMidY;
}

