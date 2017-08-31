#include "gui.h"

Gui::Gui(){
    needleX = comMidX+radius/2;
    needleY = comMidY;
    calcCameraMoveUnits();
    selectIcons();
}

void Gui::drawMenu(){
    drawIcon();
    options();
    //uniqueColoredOptions();
    drawZoom();
    drawNeedle();
    drawCompass();
    //uniqueColoredCompass();
    background();
}

std::vector<float> Gui::mouseToMenuGrid(int mouseX, int mouseY){
    std::vector<float> res;
    res.resize(3);
    res[0] = (float)mouseX/World::width;
    res[1] = 1-(float)mouseY/World::height;
    res[2] = 0;
    //std::cout<<res[0]<<"-"<<res[1]<<"-"<<res[2]<<std::endl;
    return res;
}

void Gui::background(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(backgroundColor[0],backgroundColor[1],backgroundColor[2]);
    glBegin(GL_POLYGON);
        glVertex2f(menuX[0],menuY[0]);
        glVertex2f(menuX[0],menuY[1]);
        glVertex2f(menuX[1],menuY[1]);
        glVertex2f(menuX[1],menuY[0]);
    glEnd();
}


void Gui::options(){
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
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
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
        id = xx+2;
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
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
        id = xx+4;
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
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

void Gui::uniqueColoredOptions(){
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
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
        else glColor3f(0,0,.1*(id+1));
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
        id = xx+2;
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
        else glColor3f(0,.1*(id+1),0);
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
        id = xx+4;
        if(id == World::hoverBuilding) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
        else glColor3f(.1*(id+1),0,0);
        glBegin(GL_POLYGON);
        glVertex2f(m[0]+-v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+v[1]+y);
        glVertex2f(m[0]+v[0]+x, m[1]+-v[1]+y);
        glVertex2f(m[0]+-v[0]+x, m[1]+-v[1]+y);
        glEnd();
        x += v[0]*2+f;
    }
}


void Gui::onBuildings(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton) World::buildingOption = buildingId[World::hoverBuilding];
    std::cout<<"BUILDING OPTION: "<<World::buildingOption<<std::endl;
}

void Gui::setIcons(){
    icons.clear();
    icons.resize(numIcons);
    for(int i=0; i<numIcons; i++){
        icons[i].resize(100);
    }
}

void Gui::selectIcons(){
    std::cout<<"SELECT ICONS"<<std::endl;
    setIcons();
    int i = 0;
    QSqlQuery query;
    if(query.exec("select * from "+iconsTable)) std::cout<<"icons selected"<<std::endl;
    else qDebug()<<"select icons error"<<query.lastQuery();
    while(query.next()){
        for(int r=0; r<100; r++){
            icons[i][r] = query.value(r).toInt();
        }
        i++;
    }
    numIcons = i;
    /*for(int i=0; i<1; i++){
        for(int j=0; j<(int)icons[i].size(); j++){
            std::cout<<"SEL "<<j<<" - "<<icons[i][j]<<std::endl;
        }
    }*/
}

void Gui::drawIcon(){
    float xx, yy;
    int index, ipx, ipy, p;
    p = 0;
    for(float i=0; i<numIcons; i++){
        ipx = i+p;
        ipy = i+1+p;
        index = 0;
        for(float x=0; x<10; x++){
            xx = x/100;
            for(float y=0; y<10; y++){
                yy = y/50;
                if(icons[i][index] == 1){
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    glColor3f(0,0,0);
                    glBegin(GL_POLYGON);
                    glVertex2f(iconPos[ipx]+xx-.005, iconPos[ipy]+yy+.01);
                    glVertex2f(iconPos[ipx]+xx+.005, iconPos[ipy]+yy+.01);
                    glVertex2f(iconPos[ipx]+xx+.005, iconPos[ipy]+yy-.01);
                    glVertex2f(iconPos[ipx]+xx-.005, iconPos[ipy]+yy-.01);
                    glEnd();
                }
                index++;
            }
        }
        p++;
    }
}

void Gui::zoom(){
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

void Gui::drawZoom(){
    plus();
    minus();
    //uniqueColoredPlus();
    //uniqueColoredMinus();
}

void Gui::drawUniqueColoredZoom(){

}

void Gui::plus(){
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
}

void Gui::minus(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverZoom == 1) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+-v[1]*weight);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+-v[1]*weight);
    glEnd();
}

void Gui::uniqueColoredPlus(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverZoom == 0) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,1,0);
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
}

void Gui::uniqueColoredMinus(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverZoom == 1) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+-v[1]*weight);
    glVertex2f(f*2+mid[2]+-v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+v[1]*weight);
    glVertex2f(f*2+mid[2]+v[0], mid[3]+-v[1]*weight);
    glEnd();
}

void Gui::drawCompass(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverCompass == 1) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    //for(float i=0; i<2*World::pi; i+=World::pi/12)
    for(int i=0; i<360; i++)
        glVertex2f(comMidX+(cos(i)*radius)/2, comMidY+(sin(i)*radius));
    glEnd();
}

void Gui::uniqueColoredCompass(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(World::hoverCompass == 1) glColor3f(World::hoverColor[0],World::hoverColor[1],World::hoverColor[2]);
    else glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
        glVertex2f(comMidX+(cos(i)*radius)/2, comMidY+(sin(i)*radius));
    glEnd();
}

void Gui::drawNeedle(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(needleX-.005, needleY-.01);
        glVertex2f(needleX-.005, needleY+.01);
        glVertex2f(needleX+.005, needleY+.01);
        glVertex2f(needleX+.005, needleY-.01);
    glEnd();

}

void Gui::turnCamera(std::vector<float> q){
    calcAngle(q);
    calcNeedlePos();
    turn();
}

void Gui::calcAngle(std::vector<float> q){
    float x,y,s;
    x = (q[0] - comMidX) * 2;
    y = q[1] - comMidY;
    s = sqrt(pow(x,2)+pow(y,2));
    angle = asin(y/s) * (180.0/World::pi);
    if(x<0) angle = 180 - angle;
    if(angle<0) angle = 360 + angle;
    //angle = floor(angle);
    //std::cout<<"angle "<<angle<<std::endl;
}

void Gui::calcNeedlePos(){
    needleX = (cos(angle*World::pi/180)*radius/2) + comMidX;
    needleY = (sin(angle*World::pi/180)*radius) + comMidY;
}

void Gui::turn(){
    float r;
    r = sqrt(pow(World::eyeX,2)+pow(World::eyeZ,2));
    World::eyeX = cos(angle*World::pi/180) * r;
    World::eyeZ = sin(angle*World::pi/180) * r;
}

void Gui::calcCameraMoveUnits(){
    double x, z, r;
    r = sqrt(pow(camMoveUnit[0],2)+pow(camMoveUnit[1],2));
    z = cos(angle*World::pi/180) * r;
    x = sin(angle*World::pi/180) * r;
    camMoveUnit[0] = x;
    camMoveUnit[1] = z;
    //cout<<"x: "<<x<<", z: "<<z<<endl;
}


