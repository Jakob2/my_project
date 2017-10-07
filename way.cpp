#include "way.h"

std::vector<std::vector<std::vector<float>>> Way::way;

Way::Way(){
    setWay(2);
}

void Way::setWay(int size){
    Way::way.clear();
    for(int i=0; i<size; i++){
        Way::way.push_back(std::vector<std::vector<float>>());
        for(int j=0; j<6; j++){
            Way::way[i].push_back(std::vector<float>());
            for(int k=0; k<3; k++){
                Way::way[i][j].push_back(0);
            }
        }
    }
}

void Way::selectWay(){
    QSqlQuery query;
    int index;
    index = 0;
    setWay(6);
    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b, nX,nY,nZ FROM "+Db::constructsTable+" WHERE name = 7")) std::cout<<"way selected"<<std::endl;
    else qDebug()<<"select way error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Way::way[index][0][0] = query.value(0).toFloat();
        Way::way[index][0][1] = query.value(1).toFloat();
        Way::way[index][0][2] = query.value(2).toFloat();

        Way::way[index][1][0] = query.value(3).toFloat();
        Way::way[index][1][1] = query.value(4).toFloat();
        Way::way[index][1][2] = query.value(5).toFloat();

        Way::way[index][2][0] = query.value(6).toFloat();
        Way::way[index][2][1] = query.value(7).toFloat();
        Way::way[index][2][2] = query.value(8).toFloat();

        Way::way[index][3][0] = query.value(9).toFloat();
        Way::way[index][3][1] = query.value(10).toFloat();
        Way::way[index][3][2] = query.value(11).toFloat();

        Way::way[index][4][0] = query.value(12).toFloat();
        Way::way[index][4][1] = query.value(13).toFloat();
        Way::way[index][4][2] = query.value(14).toFloat();

        Way::way[index][5][0] = query.value(15).toFloat();
        Way::way[index][5][1] = query.value(16).toFloat();
        Way::way[index][5][2] = query.value(17).toFloat();
        index++;
    }
    std::cout<<"WAY COLOR: "<<Way::way[1][4][0]<<std::endl;
}

void Way::insertWay(QString map, std::vector<std::vector<std::vector<float>>> &way, QString x, QString z, QString turn){
//void Way::insertWay(QString map, std::vector<std::vector<std::vector<float>>> &way, QString xz){
    QSqlQuery query;
    QString mid, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b, nX,nY,nZ;
    mid = id();
    for(int i=0; i<(int)Way::way.size(); i++){
        //for(int zz=0; zz<(int)Way::way[x].size(); zz++){
            //ax = QString::number(way[1][0][0]);
            ax = QString::number(way[i][0][0]);
            ay = QString::number(way[i][0][1]);
            az = QString::number(way[i][0][2]);

            bx = QString::number(way[i][1][0]);
            by = QString::number(way[i][1][1]);
            bz = QString::number(way[i][1][2]);

            cx = QString::number(way[i][2][0]);
            cy = QString::number(way[i][2][1]);
            cz = QString::number(way[i][2][2]);

            dx = QString::number(way[i][3][0]);
            dy = QString::number(way[i][3][1]);
            dz = QString::number(way[i][3][2]);

            r = QString::number(way[i][4][0]);
            g = QString::number(way[i][4][1]);
            b = QString::number(way[i][4][2]);

            nX = QString::number(way[i][5][0]);
            nY = QString::number(way[i][5][1]);
            nZ = QString::number(way[i][5][2]);

            if(query.exec("INSERT INTO "+Db::mapTable+" (id, map, name, x,y,z, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b, turn, nX,nY,nZ) VALUES ("+mid+", "+map+", '7', "+x+",0,"+z+", "+ax+","+ay+","+az+", "+bx+","+by+","+bz+", "+cx+","+cy+","+cz+", "+dx+","+dy+","+dz+", "+r+","+g+","+b+","+turn+", "+nX+","+nY+","+nZ+" )")) std::cout<<"way inserted"<<std::endl;
            else qDebug()<<"insert way error: "<<query.lastError()<<" / "<<query.lastQuery();
        //}
    }
}

void Way::drawWay(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles){
    int x, z, xx, zz;
    /*x = World::way[0];
    z = World::way[1];*/
    x = waystuff.x;
    z = waystuff.z;
    xx = floor(World::map.tile[2]-World::map.x);
    zz = floor(World::map.tile[3]-World::map.z);
    if(x < 0) x = 0;
    if(x > World::map.range-1) x = World::map.range-1;
    if(xx < 0) xx = 0;
    if(xx > World::map.range-1) xx = World::map.range-1;
    if(z < 0) z = 0;
    if(z > World::map.range-1) z = World::map.range-1;
    if(zz < 0) zz = 0;
    if(zz > World::map.range-1) zz = World::map.range-1;
    //std::cout<<"x: "<<x<<" - xx: "<<xx<<" / z: "<<z<<" - zz: "<<zz<<std::endl;
    calcAngle();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    
    if(xx>=x && zz>=z) waySouth(way,mapTiles,x,z,xx,zz);
    if(xx<=x && zz>=z) wayWest(way,mapTiles,x,z,xx,zz);
    if(xx<=x && zz<=z) wayNorth(way,mapTiles,x,z,xx,zz);
    if(xx>=x && zz<=z) wayEast(way,mapTiles,x,z,xx,zz);
    //straightWay(way,mapTiles,x,z,xx,zz);
}

/*void Way::colorway(int x, int z){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.1,0.2);
        glVertex3f(World::x+x+0,0.01,World::z+z+0);
        glVertex3f(World::x+x+1,0.01,World::z+z+0);
        glVertex3f(World::x+x+1,0.01,World::z+z+1);
        glVertex3f(World::x+x+0,0.01,World::z+z+1);
        glEnd();
    //cout<<"OFF_X: "<<X<<endl;
}*/

void Way::calcAngle(){
    std::vector<float> start;
    /*start.push_back(World::way[0]+0.5);
    start.push_back(0);
    start.push_back(World::way[1]+0.5);*/
    start.push_back(waystuff.x+.5);
    start.push_back(0);
    start.push_back(waystuff.z+.5);
    //std::cout<<start[0]<<" / "<<start[2]<<std::endl;

    std::vector<float> goal;
    goal.push_back(World::map.tile[2]-World::map.x);
    goal.push_back(0);
    goal.push_back(World::map.tile[3]-World::map.z);

    float av;
    av = Vector::absolute(Vector::direction(goal, start));

    std::vector<float> d = Vector::direction(goal,start);

    angle = asin(d[0]/av) * (180/World::pi) * -1;
    //if((World::tile[3]-World::z)<World::way[1]+0.5) angle = 180 - angle;
    //if((World::tile[2]-World::x)<World::way[0]+0.5 && (World::tile[3]-World::z)>World::way[1]+0.5) angle = 360 + angle;
    if((World::map.tile[3]-World::map.z)<waystuff.z+0.5) angle = 180 - angle;
    if((World::map.tile[2]-World::map.x)<waystuff.x+0.5 && (World::map.tile[3]-World::map.z)>waystuff.z+0.5) angle = 360 + angle;

    //std::cout<<"angle: "<<angle<<std::endl;
}

void Way::waySouth(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz){
    //std::cout<<"SOUTHWAY"<<std::endl;
    if(angle>0 && angle<45){
        for(int i=x; i<=xx; i++){
           drawStraight(way,mapTiles,i,zz+1,90,1);
           setWaySpanX(zz+1,x+1,xx+1);
        }
        for(int j=z; j<=zz; j++){
           drawStraight(way,mapTiles,x,j,0,0);
           setWaySpanZ(x+1,z+1,zz+1);
        }
    }
    else if(angle>45 && angle<90){
        for(int i=x; i<=xx; i++){
           drawStraight(way,mapTiles,i,z+1,90,1);
           setWaySpanX(z+1,x+1,xx+1);
        }
        for(int j=z; j<=zz; j++){
           //colorway(xx-1, j);
           drawStraight(way,mapTiles,xx,j,0,0);
           setWaySpanZ(xx+1,z+1,zz+1);
        }
    }
}

void Way::wayWest(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz){
    //std::cout<<"WESTWAY"<<std::endl;
    if(angle>270 && angle<315){
        for(int i=xx; i<x+1; i++){
           setWaySpanX(z+1,xx+1,x+1);
           drawStraight(way,mapTiles,i,z+1,90,1);
        }
        for(int j=z; j<=zz; j++){
           setWaySpanZ(xx+1,z+1,zz+1);
           drawStraight(way,mapTiles,xx,j,0,0);
        }
    }
    else if(angle>315 && angle<360){
        for(int i=xx; i<x+1; i++){
           setWaySpanX(zz+1,xx+1,x+1);
           drawStraight(way,mapTiles,i,zz+1,90,1);
        }
        for(int j=z; j<=zz; j++){
           setWaySpanZ(x+1,z+1,zz+1);
           drawStraight(way,mapTiles,x,j,0,0);
        }
    }
}

void Way::wayNorth(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz){
    //std::cout<<"NORTHWAY"<<std::endl;
    if(angle>180 && angle<225){
        for(int i=xx; i<x+1; i++){
           setWaySpanX(zz+1,xx+1,x+1);
           drawStraight(way,mapTiles,i,zz+1,90,1);
        }
        for(int j=zz; j<z+1; j++){
           setWaySpanZ(x+1,zz+1,z+1);
           drawStraight(way,mapTiles,x,j,0,0);
        }
    }
    else if(angle>225 && angle<270){
        for(int i=xx; i<x+1; i++){
           setWaySpanX(z+1,xx+1,x+1);
           drawStraight(way,mapTiles,i,z+1,90,1);
        }
        for(int j=zz; j<z+1; j++){
           setWaySpanZ(xx+1,zz+1,z+1);
           drawStraight(way,mapTiles,xx,j,0,0);
        }
    }
}

void Way::wayEast(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz){
    //std::cout<<"WESTWAY"<<std::endl;
    std::cout<<"angle: "<<angle<<" / x: "<<x<<" - z: "<<z<<" / xx: "<<xx<<" - zz: "<<zz<<std::endl;
    if(angle>90 && angle<135){
        for(int i=x; i<=xx; i++){
            setWaySpanX(z+1,x+1,xx+1);
            drawStraight(way,mapTiles,i,z+1,90,1);
        }
        for(int j=zz; j<z+1; j++){
            setWaySpanZ(xx+1,zz+1,z+1);
            drawStraight(way,mapTiles,xx,j,0,0);
        }
    }
    else if(angle>135 && angle<180){
        for(int i=x; i<=xx; i++){
            setWaySpanX(zz+1,x+1,xx+1);
            drawStraight(way,mapTiles,i,zz+1,90,1);
        }
        for(int j=zz; j<z+1; j++){
            setWaySpanZ(x+1,zz+1,z+1);
            drawStraight(way,mapTiles,x,j,0,0);
        }
    }
}

void Way::drawStraight(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int angle, int flag){
    float r,g,b;
    r = way[1][4][0];
    g = way[1][4][1];
    b = way[1][4][2];

    glPushMatrix();
    glTranslatef(World::map.x+x,0,World::map.z+z);
    glRotatef(angle,0,1,0);
    glTranslatef(-World::map.x-x,0,-World::map.z-z);
    glBegin(GL_POLYGON);
    //glColor3f(r,g,b);
    glColor3f(0.9,0.9,0.9);
    switch(flag){
    case 0:
        if(!mapTiles[x][z][1]) glColor3f(1,0,0);
        break;
    case 1:
        if(!mapTiles[x][z-1][1]) glColor3f(1,0,0);
        break;
    }
    glVertex3f(World::map.x+x+way[1][0][0]+.5,way[1][0][1]+.01,World::map.z+z+way[1][0][2]+.5);
    glVertex3f(World::map.x+x+way[1][1][0]+.5,way[1][1][1]+.01,World::map.z+z+way[1][1][2]+.5);
    glVertex3f(World::map.x+x+way[1][2][0]+.5,way[1][2][1]+.01,World::map.z+z+way[1][2][2]+.5);
    glVertex3f(World::map.x+x+way[1][3][0]+.5,way[1][3][1]+.01,World::map.z+z+way[1][3][2]+.5);
    glEnd();
    glPopMatrix();
}

/*void Way::straightWay(std::vector<std::vector<std::vector<float> > > &way, std::vector<std::vector<std::vector<int> > > &mapTiles, int x, int z, int xx, int zz){
    if(x+1 == xx){
        std::cout<<"SOUTHWAY x//xx"<<std::endl;
        for(int j=z; j<=zz; j++){
            drawStraight(way,mapTiles,x,j,0,0);
        }
        for(int j=zz-1; j<z+1; j++){
            drawStraight(way,mapTiles,x,j,0,0);
        }
    }
    if(z+1 == zz){
        for(int i=xx-1; i<x+1; i++){
           drawStraight(way,mapTiles,i,z+1,90,1);
        }
        for(int i=x; i<=xx; i++){
           drawStraight(way,mapTiles,i,z+1,90,1);
        }
    }
}*/

void Way::setWaySpanX(int bZ, int sX, int sXX){
    waystuff.spanX.clear();
    waystuff.baseZ = QString::number(bZ);
    for(int i=sX; i<=sXX; i++){
        waystuff.spanX.push_back(QString::number(i));
    }
}

void Way::setWaySpanZ(int bX, int sZ, int sZZ){
    waystuff.spanZ.clear();
    waystuff.baseX = QString::number(bX);
    for(int i=sZ; i<=sZZ; i++){
        waystuff.spanZ.push_back(QString::number(i));
    }
}

QString Way::id(){
    int id = 0;
    QSqlQuery query;
    if(query.exec("SELECT MAX(id) FROM "+Db::mapTable+"")) std::cout<<"max id selected"<<std::endl;
    else qDebug()<<"select max id error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()) id = query.value(0).toInt();
    return QString::number(id+1);
}
