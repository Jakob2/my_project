#include "tilemap.h"

std::vector<std::vector<std::vector<int>>> Tilemap::mapTiles;

Tilemap::Tilemap(){
    selectMapTiles();
}

void Tilemap::setMapTiles(){
    Tilemap::mapTiles.clear();
    Tilemap::mapTiles.resize(World::map.range);
    for(int x=0; x<World::map.range; x++){
        Tilemap::mapTiles[x].resize(World::map.range);
        for(int z=0; z<World::map.range; z++){
            Tilemap::mapTiles[x][z].resize(3);
        }
    }
}

void Tilemap::selectMapTiles(){
    setMapTiles();
    int x, z, color, open, traverse;
    QSqlQuery query;
    query.exec("SELECT x, z, color, open, traverse FROM "+Db::tilesTable+"");
    //if(query.exec("SELECT x, z, color, open, traverse FROM "+Db::tilesTable+"")) std::cout<<"tiles selected"<<std::endl;
    //else qDebug()<<"select tiles error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        x = query.value(0).toInt();
        z = query.value(1).toInt();
        color = query.value(2).toInt();
        open = query.value(3).toInt();
        traverse = query.value(4).toInt();
        Tilemap::mapTiles[x][z][0] = color;
        Tilemap::mapTiles[x][z][1] = open;
        Tilemap::mapTiles[x][z][2] = traverse;
    }
}

void Tilemap::ground(float x, float z, std::vector<std::vector<std::vector<int>>> &mapTiles){
    float y;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(float i=0; i<World::map.range; i++){
        int ii = i+1;
        for(float j=0; j<World::map.range; j++){
            int jj = j+1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                selectionColor(i,j, ii, jj, mapTiles[i][j][0]);
                y = sink(mapTiles[i][j][0]);
                    Shape::flatCube(0.5, i,j, x,y,z);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glLineWidth(2.0);
                glColor3f(0,0,0);
                    Shape::flatCube(0.5, i,j, x,y,z);
        }
    }
    glPopMatrix();
}

void Tilemap::unsunkenGround(float x, float z){//, std::vector<std::vector<std::vector<int> > > &mapTiles){
    float y = 0;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    for(float i=0; i<World::map.range; i++){
        for(float j=0; j<World::map.range; j++){
            glColor3f(0,0,0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glColor3f(0,0,0);
            Shape::top(i,j,x,y,z);
        }
    }
    glPopMatrix();
}

float Tilemap::sink(int type){
    float y;
    switch(type){
        case 0:
        case 1:
            y = 0;
        break;
        case 2:
            y = -0.1;
        break;
    }
    return y;
}

void Tilemap::selectionColor(int i, int j, int ii, int jj, int clr){
    switch(World::gui.areaOption){
    case 0:
    case 1:
        single(i, ii, j, jj, clr);
        break;
    case 2:
        area(i, ii, j, jj, clr);
        break;
    }
}

void Tilemap::area(int i, int ii, int j, int jj, int clr){
    float QX, X, AREA_X, QZ, Z, AREA_Z;
    QX = World::map.tile[2];
    X = World::map.x;
    //AREA_X = World::areaX;
    AREA_X = fieldstuff.areaX;
    QZ = World::map.tile[3];
    Z = World::map.z;
    //AREA_Z = World::areaZ;
    AREA_Z = fieldstuff.areaZ;
    if((i<QX-X && ii>floor(AREA_X-X)) && (j<QZ-Z && jj>floor(AREA_Z-Z))){
        glColor3f(select[0],select[1],select[2]);
    }
    else if((i>=floor(QX-X) && i-1<floor(AREA_X-X)) && (j<QZ-Z && jj>floor(AREA_Z-Z))){
        glColor3f(select[0],select[1],select[2]);
    }
    else if((i>=floor(QX-X) && i-1<floor(AREA_X-X)) && (j>=floor(QZ-Z) && j-1<floor(AREA_Z-Z))){
        glColor3f(select[0],select[1],select[2]);
    }
    else if((i<QX-X && ii>floor(AREA_X-X)) && (j>=floor(QZ-Z) && j-1<floor(AREA_Z-Z))){
        glColor3f(select[0],select[1],select[2]);
    }
    else{
       parseColor(clr);
       glColor3f(color[0],color[1],color[2]);
    }
}

void Tilemap::single(int i, int ii, int j, int jj, int clr){
    float qx, x, qz, z;
    qx = World::map.tile[2];
    qz = World::map.tile[3];
    x = World::map.x;
    z = World::map.z;

    if((i<qx-x && ii>qx-x) && (j<qz-z && jj>qz-z)){
        glColor3f(select[0],select[1],select[2]);
    }
    else{
       parseColor(clr);
       glColor3f(color[0],color[1],color[2]);
    }
}

void Tilemap::parseColor(int c){
    switch(c){
    case 0:
        color[0] = grass[0];
        color[1] = grass[1];
        color[2] = grass[2];
    break;
    case 1:
        color[0] = desert[0];
        color[1] = desert[1];
        color[2] = desert[2];
    break;
    case 2:
        color[0] = water[0];
        color[1] = water[1];
        color[2] = water[2];
    break;
    }
}

/*void Tilemap::constructs(std::vector<std::vector<std::vector<float>>> &construct, float xPos, float zPos){
    float QX, QZ, X, Z;
    QX = World::intersectionX;
    QZ = World::intersectionZ;
    X = World::x;
    Z = World::z;
    float x,y,z, r, g, b, xx, zz;
    int turn;
    tIndex = 0;

    for(int i=0; i<(int)construct.size(); i++){
        x = construct[i][4][0]-0.5;
        y = construct[i][4][1];
        z = construct[i][4][2]-0.5;
        turn = construct[i][5][1];
        r = construct[i][6][0];
        g = construct[i][6][1];
        b = construct[i][6][2];
        xx = x+1;
        zz = z+1;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if(construct[i][5][0] == World::buildingOption){
            glTranslatef(xPos+x,y,zPos+z);
            glRotatef(0,0,1,0);
            glTranslatef(-xPos-x,-y,-zPos-z);
            glColor3f(0,1,1);
            corpus(construct, i, x,y,z, xPos, zPos);
            setToken(i, construct);
        }else{
            glTranslatef(xPos+x,y,zPos+z);
            glRotatef(turn,0,1,0);
            glTranslatef(-xPos-x,-y,-zPos-z);

            if((x-clip<QX-X && xx-clip>QX-X) && (z-clip<QZ-Z && zz-clip>QZ-Z) && World::moveConstruct) World::buildingOption = construct[i][5][0];
            else glColor3f(r,g,b);
            glColor3f(r,g,b);
            corpus(construct, i, x,y,z, xPos, zPos);
        }
        glEnd();
        glPopMatrix();
    }
}

void Tilemap::initToken(){
    token.resize(tIndex+1);
    for(int i=0; i<tIndex+1; i++){
        token[i].resize(4);
        for(int j=0; j<(int)token[i].size(); j++){
            token[i][j].resize(3);
        }
    }
}

void Tilemap::setToken(int i, std::vector<std::vector<std::vector<float>>> &construct){
    initToken();
    token[tIndex][0][0] = construct[i][0][0];
    token[tIndex][0][1] = construct[i][0][1];
    token[tIndex][0][2] = construct[i][0][2];

    token[tIndex][1][0] = construct[i][1][0];
    token[tIndex][1][1] = construct[i][1][1];
    token[tIndex][1][2] = construct[i][1][2];

    token[tIndex][2][0] = construct[i][2][0];
    token[tIndex][2][1] = construct[i][2][1];
    token[tIndex][2][2] = construct[i][2][2];

    token[tIndex][3][0] = construct[i][3][0];
    token[tIndex][3][1] = construct[i][3][1];
    token[tIndex][3][2] = construct[i][3][2];
    tIndex++;
}*/
