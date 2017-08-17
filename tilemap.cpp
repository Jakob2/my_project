#include "tilemap.h"

std::vector<std::vector<std::vector<int>>> Tilemap::mapTiles;

Tilemap::Tilemap(){
    selectMapTiles();
}

void Tilemap::setMapTiles(){
    Tilemap::mapTiles.clear();
    Tilemap::mapTiles.resize(World::range);
    for(int x=0; x<World::range; x++){
        Tilemap::mapTiles[x].resize(World::range);
        for(int z=0; z<World::range; z++){
            Tilemap::mapTiles[x][z].resize(3);
        }
    }
}

void Tilemap::selectMapTiles(){
    setMapTiles();
    int x, z, color, open, traverse;
    QSqlQuery query;
    if(query.exec("SELECT x, z, color, open, traverse FROM "+tilesTable+"")) std::cout<<"tiles selected"<<std::endl;
    else qDebug()<<"select tiles error: "<<query.lastError()<<" / "<<query.lastQuery();
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
    for(float i=0; i<World::range; i++){
        int ii = i+1;
        for(float j=0; j<World::range; j++){
            int jj = j+1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                selectionColor(i,j, ii, jj, mapTiles[i][j][0]);
                y = sink(mapTiles[i][j][0]);
                    flatCube(0.5, i,j, x,y,z);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glLineWidth(2.0);
                glColor3f(0,0,0);
                    flatCube(0.5, i,j, x,y,z);
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
    switch(World::option){
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
    QX = World::intersectionX;
    X = World::x;
    AREA_X = World::areaX;
    QZ = World::intersectionZ;
    Z = World::z;
    AREA_Z = World::areaZ;
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
    float QX, X, QZ, Z;
    QX = World::intersectionX;
    X = World::x;
    QZ = World::intersectionZ;
    Z = World::z;
    if((i<QX-X && ii>QX-X) && (j<QZ-Z && jj>QZ-Z)){
        /*CURRENT_TILE_X = i;
        CURRENT_TILE_Z = j;*/
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
