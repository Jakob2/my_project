#include "mouseray.h"

Mouseray::Mouseray(){

}

void Mouseray::calculateGLCoords(int x, int y){
    //glClear(GL_DEPTH_BUFFER_BIT);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    e = {World::eyeX, World::eyeY, World::eyeZ};
    p = {posX, posY, posZ};
    intersect(Vector::direction(e,p));
}

void Mouseray::intersect(std::vector<float> in){
    float x, y, z, r, t, xx, yy, zz;
    x = in[0];
    y = in[1];
    z = in[2];
    r = ((-World::eyeY*x) + (y*World::eyeX)) / y;
    t = (World::eyeX-r) / -x;
    xx = World::eyeX + (t * x);
    yy = World::eyeY + (t * y);
    zz = World::eyeZ + (t * z);
    intersection[0] = xx;
    intersection[1] = yy;
    intersection[2] = zz;
    std::cout<<"INTERSECTION: "<<xx<<"-"<<yy<<"-"<<zz<<std::endl;
}

bool Mouseray::panelWorld(std::vector<float> in){
    bool out = false;
    if(in[0]>0 && in[0]<0.75 && in[1]>0 && in[1]<1) out = true;
    return out;
}

