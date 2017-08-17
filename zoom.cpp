#include "zoom.h"

Zoom::Zoom(){

}

void Zoom::zoom(){
    switch(World::hoverZoom){
    case 0:
        if(World::zoom<1) World::zoom += .1;
        break;
    case 1:
        if(World::zoom>0.2) World::zoom -= .1;
        break;
    }
    std::cout<<"ZOOM: "<<World::zoom<<std::endl;
}

void Zoom::drawZoom(){
    plus();
    minus();
}

bool Zoom::panelZoom(std::vector<float> mouse){
    bool out = false;
    if((mouse[0]>f+mid[0]-v[0] && mouse[0]<f*2+mid[2]+v[0]) && (mouse[1]>mid[1]-v[1] && mouse[1]<mid[3]+v[1])) out = true;
    else World::hoverZoom = -1;
    return out;
}

void Zoom::hoverZoom(std::vector<float> mouse){
    if((mouse[0]>f+mid[0]-v[0] && mouse[0]<f+mid[0]+v[0]) && (mouse[1]>mid[1]-v[1] && mouse[1]<mid[1]+v[1])) World::hoverZoom = 0;
    if((mouse[0]>f*2+mid[2]-v[0] && mouse[0]<f*2+mid[2]+v[0]) && (mouse[1]>mid[3]-v[1] && mouse[1]<mid[3]+v[1])) World::hoverZoom = 1;
    //std::cout<<"ZOOM: "<<World::hoverZoom<<std::endl;
}

void Zoom::plus(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverZoom == 0) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(f+mid[0]+-v[0], mid[1]+-v[1]*weight);
    glVertex2f(f+mid[0]+-v[0], mid[1]+v[1]*weight);
    glVertex2f(f+mid[0]+v[0], mid[1]+v[1]*weight);
    glVertex2f(f+mid[0]+v[0], mid[1]+-v[1]*weight);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(f+mid[0]+-v[0]*weight, mid[1]+-v[1]);
    glVertex2f(f+mid[0]+-v[0]*weight, mid[1]+v[1]);
    glVertex2f(f+mid[0]+v[0]*weight, mid[1]+v[1]);
    glVertex2f(f+mid[0]+v[0]*weight, mid[1]+-v[1]);
    glEnd();
    /*glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex2f(f+mid[0]+-v[0], mid[1]+v[1]);
    glVertex2f(f+mid[0]+v[0], mid[1]+v[1]);
    glVertex2f(f+mid[0]+v[0], mid[1]-v[1]);
    glVertex2f(f+mid[0]+-v[0], mid[1]-v[1]);
    glEnd();*/
}

void Zoom::minus(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverZoom == 1) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+-v[1]*weight);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+-v[1]*weight);
    glEnd();
    /*glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+v[1]);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+v[1]);
    glVertex2f(f*2+mid[2]+v[0], mid[3]-v[1]);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]-v[1]);
    glEnd();*/
}

