#include "icon.h"

Icon::Icon(){
    selectIcons();
}

void Icon::setIcons(){
    icons.clear();
    icons.resize(numIcons);
    for(int i=0; i<numIcons; i++){
        icons[i].resize(100);
    }
}

void Icon::selectIcons(){
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

void Icon::drawIcon(){
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
                yy = y/100;
                if(icons[i][index] == 1){
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    glColor3f(0,0,0);
                    glBegin(GL_POLYGON);
                    glVertex2f(iconPos[ipx]+xx-.005, iconPos[ipy]+yy+.005);
                    glVertex2f(iconPos[ipx]+xx+.005, iconPos[ipy]+yy+.005);
                    glVertex2f(iconPos[ipx]+xx+.005, iconPos[ipy]+yy-.005);
                    glVertex2f(iconPos[ipx]+xx-.005, iconPos[ipy]+yy-.005);
                    glEnd();
                }
                index++;
            }
        }
        p++;
    }
}

