#include "shape.h"

/*Shape::Shape(){

}*/

void Shape::top(int i, int j, float x, float y, float z){
    glBegin(GL_POLYGON);//a,b,f,e TOP
        glNormal3f(0,1,0);
        glVertex3f(i+x+0, y+0, j+z+0);
        glVertex3f(i+x+1, y+0, j+z+0);
        glVertex3f(i+x+1, y+0, j+z+1);
        glVertex3f(i+x+0, y+0, j+z+1);
    glEnd();
}

void Shape::left(float depth, int i, int j, float x, float y, float z){
    glBegin(GL_POLYGON);//a,e,g,c LEFT
        glVertex3f(i+x+0, y+0, j+z+0);
        glVertex3f(i+x+0, y+0, j+z+1);
        glVertex3f(i+x+0, y+(-depth), j+z+1);
        glVertex3f(i+x+0, y+(-depth), j+z+0);
    glEnd();
}

void Shape::back(float depth, int i, int j, float x, float y, float z){
    glBegin(GL_POLYGON);//e,g,h,f BACK
        glVertex3f(i+x+0, y+0, j+z+1);
        glVertex3f(i+x+0, y+(-depth), j+z+1);
        glVertex3f(i+x+1, y+(-depth), j+z+1);
        glVertex3f(i+x+1, y+0, j+z+1);
    glEnd();
}

void Shape::right(float depth, int i, int j, float x, float y, float z){
    glBegin(GL_POLYGON);//f,h,d,b RIGHT
        glVertex3f(i+x+1, y+0, j+z+1);
        glVertex3f(i+x+1, y+(-depth), j+z+1);
        glVertex3f(i+x+1, y+(-depth), j+z+0);
        glVertex3f(i+x+1, y+0, j+z+0);
    glEnd();
}

void Shape::front(float depth, int i, int j, float x, float y, float z){
    glBegin(GL_POLYGON);//a,b,d,c FRONT
        glVertex3f(i+x+0, y+0, j+z+0);
        glVertex3f(i+x+1, y+0, j+z+0);
        glVertex3f(i+x+1, y+(-depth), j+z+0);
        glVertex3f(i+x+0, y+(-depth), j+z+0);
    glEnd();
}

void Shape::flatCube(float depth, int i, int j, float x, float y, float z){
    Shape::top(i,j, x,y,z);
    Shape::left(depth, i,j, x,y,z);
    Shape::back(depth, i,j, x,y,z);
    Shape::right(depth, i,j, x,y,z);
    Shape::front(depth, i,j, x,y,z);
}

void Shape::corpus(std::vector<std::vector<std::vector<float>>> &construct, int i, float x, float y, float z, float xPos, float zPos){
    /*std::vector<float> a;
    std::vector<float> b;
    std::vector<float> d;
    std::vector<float> vb;
    std::vector<float> vd;
    std::vector<float> k;
    a = {xPos+x+construct[i][0][0], y+construct[i][0][1], zPos+z+construct[i][0][2]};
    b = {xPos+x+construct[i][1][0], y+construct[i][1][1], zPos+z+construct[i][1][2]};
    d = {xPos+x+construct[i][3][0], y+construct[i][3][1], zPos+z+construct[i][3][2]};
    vb = Vector::direction(a,b);
    vd = Vector::direction(a,d);
    k = Vector::normalize(Vector::normal(vd,vb));*/
    float nx,ny,nz;
    nx = construct[i][7][0]*-1;
    ny = construct[i][7][1]*-1;
    nz = construct[i][7][2]*-1;
    //std::cout<<"i: "<<i<<" / "<<k[0]<<" / "<<k[1]<<" / "<<k[2]<<std::endl;
    glBegin(GL_POLYGON);
        glNormal3f(nx, ny, nz);
        glVertex3f(xPos+x+construct[i][0][0], y+construct[i][0][1], zPos+z+construct[i][0][2]);
        glVertex3f(xPos+x+construct[i][1][0], y+construct[i][1][1], zPos+z+construct[i][1][2]);
        glVertex3f(xPos+x+construct[i][2][0], y+construct[i][2][1], zPos+z+construct[i][2][2]);
        glVertex3f(xPos+x+construct[i][3][0], y+construct[i][3][1], zPos+z+construct[i][3][2]);
}

/*void Shape::wireToken(std::vector<std::vector<std::vector<float>>> token, float clip, int x, int z, float offX, float offZ, std::vector<std::vector<std::vector<int>>> &mapTiles){
    //float clip = 0.5;
    for(int i=0; i<(int)token.size(); i++){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if(!mapTiles[x][z][1]){
            World::validPlace = 0;
            glColor3f(1,0,0);
        }
        else{
            World::validPlace = 1;
            glColor3f(0.9,0.9,0.9);
        }
        glBegin(GL_POLYGON);
            glVertex3f(offX+clip+x+token[i][0][0], token[i][0][1], offZ+clip+z+token[i][0][2]);
            glVertex3f(offX+clip+x+token[i][1][0], token[i][1][1], offZ+clip+z+token[i][1][2]);
            glVertex3f(offX+clip+x+token[i][2][0], token[i][2][1], offZ+clip+z+token[i][2][2]);
            glVertex3f(offX+clip+x+token[i][3][0], token[i][3][1], offZ+clip+z+token[i][3][2]);
        glEnd();
    }
}*/
