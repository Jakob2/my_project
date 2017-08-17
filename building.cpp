#include "building.h"

Building::Building(){
    setMargin();
}

void Building::options(){
    int id;
    float x, y;
    x = 0;
    y = 0;
    std::vector<float> m, v;
    m = margin;
    v = vertice;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(int xx=0; xx<2; xx++){
        id = xx;
        if(id == World::hoverBuilding) glColor3f(.5,.5,0);
        else glColor3f(0,0,.75);
        glBegin(GL_POLYGON);
        glVertex2f(m[0]+-v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+-v[1]+y);
        glVertex2f(m[0]+-v[0]+x, m[1]+-v[1]+y);
        glEnd();
        x += v[0]*2+f;
    }
    x = 0;
    y = -(v[1]*2+f);
    for(int xx=0; xx<2; xx++){
        id = xx+3;
        if(id == World::hoverBuilding) glColor3f(.5,.5,0);
        else glColor3f(0,0,.75);
        glBegin(GL_POLYGON);
        glVertex2f(m[0]+-v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+-v[1]+y);
        glVertex2f(m[0]+-v[0]+x, m[1]+-v[1]+y);
        glEnd();
        x += v[0]*2+f;
    }
    x = 0;
    y = -(v[1]*4+f*2);
    for(int xx=0; xx<2; xx++){
        id = xx+6;
        if(id == World::hoverBuilding) glColor3f(.5,.5,0);
        else glColor3f(0,0,.75);
        glBegin(GL_POLYGON);
        glVertex2f(m[0]+-v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+-v[1]+y);
        glVertex2f(m[0]+-v[0]+x, m[1]+-v[1]+y);
        glEnd();
        x += v[0]*2+f;
    }
}

void Building::hoverBuildings(std::vector<float> mouse){
    std::vector<float> m, v;
    m = margin;
    v = vertice;
    float x, y;
    x = 0;
    y = 0;
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 0;
        //std::cout<<"hovering 1"<<std::endl;
    }
    x += v[0]*2+f;
    y = 0;
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 1;
        //std::cout<<"hovering 2"<<std::endl;
    }
    x = 0;
    y = -(v[1]*2+f);
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 3;
        //std::cout<<"hovering 3"<<std::endl;
    }
    x += v[0]*2+f;
    y = -(v[1]*2+f);
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 4;
        //std::cout<<"hovering 4"<<std::endl;
    }
    x = 0;
    y = -(v[1]*4+f*2);
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 6;
        //std::cout<<"hovering 5"<<std::endl;
    }
    x += v[0]*2+f;
    y = -(v[1]*4+f*2);
    if((mouse[0]>m[0]+-v[0]+x && mouse[0]<m[0]+v[0]+x) && (mouse[1]>m[1]-v[1]+y && mouse[1]<m[1]+v[1]+y)){
        World::hoverBuilding = 7;
        //std::cout<<"hovering 6"<<std::endl;
    }
}

bool Building::panelBuildings(std::vector<float> mouse){
    bool out = false;
    if(mouse[0]>margin[0]-vertice[0] && mouse[0]<margin[0]+vertice[0]+vertice[0]*2+f && mouse[1]>margin[1]-(vertice[1]*4+f*2)-vertice[1] && mouse[1]<1) out = true;
    else World::hoverBuilding = -1;
    return out;
}

void Building::setMargin(){
    margin[0] = 0.75 + vertice[0] + 0.01;
    margin[1] = 1 - vertice[1] - 0.01;
}
