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
    p = {(float)posX, (float)posY, (float)posZ};
    intersect(Vector::direction(e,p));
}

std::vector<float> Mouseray::calculateGLCoordsTest(int x, int y){
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    e = {World::eyeX, World::eyeY, World::eyeZ};
    p = {(float)posX, (float)posY, (float)posZ};
    return intersectTest(Vector::direction(e,p));
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
    float txx, tzz;
    txx = floor(xx-World::x);
    tzz = floor(zz-World::z);
    if(txx<0) txx = 0;
    if(tzz<0) tzz = 0;
    World::tile = {(float)floor(xx),(float)floor(zz),(float)xx,(float)zz,(float)floor(xx-World::x),(float)floor(zz-World::z)};
    //World::tile = {(float)floor(xx),(float)floor(zz),(float)xx,(float)zz,txx,tzz};

    //std::cout<<"TILE: "<<World::tile[0]<<"-"<<World::tile[1]<<" // "<<World::tile[2]<<"-"<<World::tile[3]<<" // "<<World::tile[4]<<"-"<<World::tile[5]<<std::endl;
    //std::cout<<"INTERSECTION: "<<xx<<"-"<<yy<<"-"<<zz<<std::endl;
}

std::vector<float> Mouseray::intersectTest(std::vector<float> in){
    float x, y, z, r, t, xx, yy, zz;
    x = in[0];
    y = in[1];
    z = in[2];
    r = ((-World::eyeY*x) + (y*World::eyeX)) / y;
    t = (World::eyeX-r) / -x;
    xx = World::eyeX + (t * x);
    yy = World::eyeY + (t * y);
    zz = World::eyeZ + (t * z);
    //return {(float)floor(xx-World::x),yy,(float)floor(zz-World::z)};
    std::vector<float> out = {xx,yy,zz};
    return out;
}

bool Mouseray::panelWorld(std::vector<float> in){
    bool out = false;
    if(in[0]>0 && in[0]<0.75 && in[1]>0 && in[1]<1) out = true;
    return out;
}

void Mouseray::crossfade(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(5.0);
    glColor3f(.5,.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(-.1+World::tile[2],.01,.1+World::tile[3]);
    glVertex3f(.1+World::tile[2],.01,.1+World::tile[3]);
    glVertex3f(.1+World::tile[2],.01,-.1+World::tile[3]);
    glVertex3f(-.1+World::tile[2],.01,-.1+World::tile[3]);
    glEnd();
}

bool Mouseray::checkIfOnTilemap(int x, int y){
    readPixelColor(x,y);
    if(!pickedId){
        //std::cout<<"ON TILEMAP !!!"<<std::endl;
        return true;
    }
    else{
        //std::cout<<"NOT ON TILEMAP !!!"<<std::endl;
        return false;
    }
}

/*bool Mouseray::hoverGui(int x, int y){
    switch(pickedId){
    case 1703936:
        World::hoverBuilding = 0;
        return true;
        break;
    case 3342336:
        World::hoverBuilding = 1;
        return true;
        break;
    case 19456:
        World::hoverBuilding = 2;
        return true;
        break;
    case 26112:
        World::hoverBuilding = 3;
        return true;
        break;
    case 128:
        World::hoverBuilding = 4;
        return true;
        break;
    case 153:
        World::hoverBuilding = 5;
        return true;
        break;
    case 255:
        World::hoverCompass = 1;
        return true;
        break;
    case 65280:
        World::hoverZoom = 0;
        return true;
        break;
    case 16711680:
        World::hoverZoom = 1;
        return true;
        break;
    case 32896:
        //std::cout<<"HOVERCOLOR"<<std::endl;
        return true;
        break;
    default:
        World::hoverBuilding = -1;
        World::hoverZoom = -1;
        World::hoverCompass = -1;
        return false;
        break;
    }
    //std::cout<<"BUILDING OPTION ID: "<<World::buildingOption<<" / "<<World::hoverBuilding<<std::endl;
}*/

void Mouseray::readPixelColor(int x, int y){
    //glFlush();
    //glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char pixelcolor[3];
    glReadPixels(x,World::height-y, 1,1, GL_RGB,GL_UNSIGNED_BYTE, pixelcolor);
    //std::cout<<pixelcolor[0]<<"-"<<pixelcolor[1]<<"-"<<pixelcolor[2]<<"-"<<pixelcolor[3]<<"-"<<std::endl;
    pickedId = pixelcolor[0] + pixelcolor[1] * 256 + pixelcolor[2] * 256*256;
    World::pickedColor = pixelcolor[0] + pixelcolor[1] * 256 + pixelcolor[2] * 256*256;
    //std::cout<<"PIXELID: "<<pickedId<<std::endl;
}
