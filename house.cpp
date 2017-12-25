#include "house.h"

House::House(){

}

House::House(int name){
    selectHouse(name, 1);
}

void House::selectHouse(int name, int map){
    initPolygon(7);
    int index = 0;
    QSqlQuery query;
    //if(query.exec("select ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, ax,ay,az, ax,ax, r,g,b, nX,nY,nZ from "+Db::constructsTable+" where name = "+QString::number(name))) std::cout<<"house selected by name"<<std::endl;
    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, x,y,z, id,turn, r,g,b, nX,nY,nZ FROM "+Db::mapTable+" WHERE name = "+QString::number(name)+" and map="+QString::number(map)+"")) std::cout<<"house selected by name"<<std::endl;
    else qDebug()<<"select house by name error"<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        polygon[index][0][0] = query.value(0).toFloat(); //ax
        polygon[index][0][1] = query.value(1).toFloat(); //ay
        polygon[index][0][2] = query.value(2).toFloat(); //az

        polygon[index][1][0] = query.value(3).toFloat(); //bx
        polygon[index][1][1] = query.value(4).toFloat(); //by
        polygon[index][1][2] = query.value(5).toFloat(); //bz

        polygon[index][2][0] = query.value(6).toFloat(); //cx
        polygon[index][2][1] = query.value(7).toFloat(); //cy
        polygon[index][2][2] = query.value(8).toFloat(); //cz

        polygon[index][3][0] = query.value(9).toFloat(); //dx
        polygon[index][3][1] = query.value(10).toFloat(); //dy
        polygon[index][3][2] = query.value(11).toFloat(); //dz

        polygon[index][4][0] = query.value(12).toFloat(); //map x
        polygon[index][4][1] = query.value(13).toFloat(); //map y
        polygon[index][4][2] = query.value(14).toFloat(); //map z

        polygon[index][5][0] = query.value(15).toFloat(); //id
        polygon[index][5][1] = query.value(16).toFloat(); //turn
        polygon[index][5][2] = 0; //free slot

        polygon[index][6][0] = query.value(17).toFloat(); //r
        polygon[index][6][1] = query.value(18).toFloat(); //g
        polygon[index][6][2] = query.value(19).toFloat(); //b

        polygon[index][7][0] = query.value(20).toFloat(); //nX
        polygon[index][7][1] = query.value(21).toFloat(); //nY
        polygon[index][7][2] = query.value(22).toFloat(); //nZ
        index++;
    }
}

void House::renderHouse(float xPos, float zPos){
    std::cout<<"render call"<<std::endl;
    float x,y,z, r, g, b;
    int turn;
    for(int i=0; i<(int)polygon.size(); i++){
        x = polygon[i][4][0]-0.5;
        y = polygon[i][4][1];
        z = polygon[i][4][2]-0.5;
        /*x = .5;
        y = 0;
        z = .5;*/
        turn = polygon[i][5][1];
        r = polygon[i][6][0];
        g = polygon[i][6][1];
        b = polygon[i][6][2];

        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        /*glTranslatef(xPos+x,y,zPos+z);
        glRotatef(turn,0,1,0);
        glTranslatef(-xPos-x,-y,-zPos-z);*/

        const GLfloat light_position[] = { .0f, .0f, .0f, .5f };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        /*std::vector<float> d;
        d = Vector::direction({0,0,0},{x+xPos,0,z+zPos});
        float distance;
        distance = Vector::absolute(d);*/

        if(polygon[i][4][0]-1 == World::map.tile[4] && polygon[i][4][2]-1 == World::map.tile[5]) World::map.constructId = polygon[i][5][0];
        if(polygon[i][5][0] == World::map.constructId){
            glColor3f(0,1,1);
            corpus(i, x,y,z, xPos,zPos);
        }else{
            //if(distance > 4) glColor3f(r-.5,g-.5,b-.5);
            //else glColor3f(r,g,b);
            glColor3f(r,g,b);
            corpus(i, x,y,z, xPos,zPos);
        }

        //glEnd();
        glPopMatrix();
     }
}

void House::corpus(int i, float x, float y, float z, float xPos, float zPos){
    float nx,ny,nz;
    nx = polygon[i][7][0]*-1;
    ny = polygon[i][7][1]*-1;
    nz = polygon[i][7][2]*-1;
    glBegin(GL_POLYGON);
        glNormal3f(nx, ny, nz);
        glVertex3f(xPos+x+polygon[i][0][0], y+polygon[i][0][1], zPos+z+polygon[i][0][2]);
        glVertex3f(xPos+x+polygon[i][1][0], y+polygon[i][1][1], zPos+z+polygon[i][1][2]);
        glVertex3f(xPos+x+polygon[i][2][0], y+polygon[i][2][1], zPos+z+polygon[i][2][2]);
        glVertex3f(xPos+x+polygon[i][3][0], y+polygon[i][3][1], zPos+z+polygon[i][3][2]);
    glEnd();
}


void House::initPolygon(int size){
    polygon.clear();
    for(int h=0; h<size; h++){
        polygon.push_back(std::vector<std::vector<float>>());
        for(int i=0; i<vectorMainSize; i++){
             polygon[h].push_back(std::vector<float>());
             for(int j=0; j<vectorSubSize; j++){
                 polygon[h][i].resize(3);
             }
        }
    }
}

