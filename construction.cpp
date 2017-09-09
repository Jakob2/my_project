#include "construction.h"

std::vector<std::vector<std::vector<float>>> Construction::construct;

Construction::Construction(){
    selectConstructs(QString::number(1));
}

void Construction::setConstruct(int size){
    Construction::construct.clear();
    for(int i=0; i<size; i++){
        Construction::construct.push_back(std::vector<std::vector<float>>());
        for(int j=0; j<7; j++){
            Construction::construct[i].push_back(std::vector<float>());
            for(int k=0; k<3; k++){
                Construction::construct[i][j].push_back(0);
            }
        }
    }
}

void Construction::selectConstructs(QString map){
    int index = 0;
    int range;
    QSqlQuery query;
    if(query.exec("SELECT COUNT(*) FROM "+Db::mapTable+" WHERE map="+map+"")) std::cout<<"construct range selected"<<std::endl;
    else qDebug()<<"construct range error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()) range = query.value(0).toInt();
    setConstruct(range);
    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, x,y,z, id,turn, r,g,b FROM "+Db::mapTable+" WHERE map="+map+"")) std::cout<<"constrcuts selected"<<std::endl;
    else qDebug()<<"select construct error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Construction::construct[index][0][0] = query.value(0).toFloat(); //ax
        Construction::construct[index][0][1] = query.value(1).toFloat(); //ay
        Construction::construct[index][0][2] = query.value(2).toFloat(); //az

        Construction::construct[index][1][0] = query.value(3).toFloat(); //bx
        Construction::construct[index][1][1] = query.value(4).toFloat(); //by
        Construction::construct[index][1][2] = query.value(5).toFloat(); //bz

        Construction::construct[index][2][0] = query.value(6).toFloat(); //cx
        Construction::construct[index][2][1] = query.value(7).toFloat(); //cy
        Construction::construct[index][2][2] = query.value(8).toFloat(); //cz

        Construction::construct[index][3][0] = query.value(9).toFloat(); //dx
        Construction::construct[index][3][1] = query.value(10).toFloat(); //dy
        Construction::construct[index][3][2] = query.value(11).toFloat(); //dz

        Construction::construct[index][4][0] = query.value(12).toFloat(); //map x
        Construction::construct[index][4][1] = query.value(13).toFloat(); //map y
        Construction::construct[index][4][2] = query.value(14).toFloat(); //map z

        Construction::construct[index][5][0] = query.value(15).toFloat(); //id
        Construction::construct[index][5][1] = query.value(16).toFloat(); //turn

        Construction::construct[index][6][0] = query.value(17).toFloat(); //r
        Construction::construct[index][6][1] = query.value(18).toFloat(); //g
        Construction::construct[index][6][2] = query.value(19).toFloat(); //b
        index++;
    }
    /*for(int i=0; i<(int)Db::construct.size(); i++){
           for(int j=0; j<(int)Db::construct[i].size(); j++){
               for(int k=0; k<(int)Db::construct[i][j].size(); k++){
                   cout<<i<<"/"<<j<<"/"<<k<<"/"<<Db::construct[i][j][k]<<endl;
               }
           }
    }*/
}

void Construction::insertConstruct(QString map, QString name, QString x, QString z){
    QString ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b;
    std::vector<std::vector<float>> test;
    int index = 0;
    int range = 0;
    QString mid = id();
    QSqlQuery query;
    query.exec("SELECT ax FROM "+Db::constructsTable+" WHERE name="+name+"");
    while(query.next()){
        range++;
    }
    //test.clear();
    test.resize(range);
    for(int i=0; i<range; i++){
        test[i].resize(15);
    }
    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b FROM "+Db::constructsTable+" WHERE name="+name+"")) std::cout<<"name selected"<<std::endl;
    else qDebug()<<"select name error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        for(int i=0; i<15; i++){
            test[index][i] = query.value(i).toFloat();
        }
        index++;
    }
    for(int i=0; i<(int)test.size(); i++){
        ax = QString::number(test[i][0]);
        ay = QString::number(test[i][1]);
        az = QString::number(test[i][2]);

        bx = QString::number(test[i][3]);
        by = QString::number(test[i][4]);
        bz = QString::number(test[i][5]);

        cx = QString::number(test[i][6]);
        cy = QString::number(test[i][7]);
        cz = QString::number(test[i][8]);

        dx = QString::number(test[i][9]);
        dy = QString::number(test[i][10]);
        dz = QString::number(test[i][11]);

        r = QString::number(test[i][12]);
        g = QString::number(test[i][13]);
        b = QString::number(test[i][14]);

        if(query.exec("INSERT INTO "+Db::mapTable+" (id, map, name, x,y,z, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b) VALUES ("+mid+", "+map+", "+name+", "+x+",0,"+z+", "+ax+","+ay+","+az+", "+bx+","+by+","+bz+", "+cx+","+cy+","+cz+", "+dx+","+dy+","+dz+", "+r+","+g+","+b+" )")) std::cout<<"construct inserted"<<std::endl;
        else qDebug()<<"insert construct error: "<<query.lastError()<<" / "<<query.lastQuery();
    }
}

void Construction::updateTilesOpen(QString x, QString z){
    QSqlQuery query;
    if(query.exec("update "+Db::tilesTable+" set open = 0 where x = "+x+" and z = "+z)) std::cout<<"tiles open updated"<<std::endl;
    else qDebug()<<"update tiles open error"<<query.lastError()<<" / "<<query.lastQuery();
}

void Construction::deleteConstruct(QString id){
    QSqlQuery query;
    if(query.exec("delete from "+Db::mapTable+" where id = "+id)) std::cout<<"construct deleted"<<std::endl;
    else qDebug()<<"delete construct error"<<query.lastError()<<" / "<<query.lastQuery();
}

QString Construction::id(){
    int id = 0;
    QSqlQuery query;
    if(query.exec("SELECT MAX(id) FROM "+Db::mapTable+"")) std::cout<<"max id selected"<<std::endl;
    else qDebug()<<"select max id error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()) id = query.value(0).toInt();
    return QString::number(id+1);
}

void Construction::constructs(std::vector<std::vector<std::vector<float>>> &construct, float xPos, float zPos){
    float QX, QZ, X, Z;
    QX = World::tile[2];
    QZ = World::tile[3];
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

        if(construct[i][4][0]-1 == World::tile[4] && construct[i][4][2]-1 == World::tile[5]) World::constructId = construct[i][5][0];
        //else World::constructId = -1;
        //if(World::constructId != -1) std::cout<<"CONSTRUCT ID: "<<World::constructId<<std::endl;

        //if(construct[i][5][0] == World::buildingOption){
        if(construct[i][5][0] == World::constructId){
            glTranslatef(xPos+x,y,zPos+z);
            glRotatef(turn,0,1,0);
            glTranslatef(-xPos-x,-y,-zPos-z);
            glColor3f(0,1,1);
            Shape::corpus(construct, i, x,y,z, xPos, zPos);
            //setToken(i, construct);
        }else{
            glTranslatef(xPos+x,y,zPos+z);
            glRotatef(turn,0,1,0);
            glTranslatef(-xPos-x,-y,-zPos-z);

            if((x-clip<QX-X && xx-clip>QX-X) && (z-clip<QZ-Z && zz-clip>QZ-Z) && World::moveConstruct) World::buildingOption = construct[i][5][0];
            else glColor3f(r,g,b);
            glColor3f(r,g,b);
            Shape::corpus(construct, i, x,y,z, xPos, zPos);
        }
        glEnd();
        glPopMatrix();
    }
}

void Construction::initToken(int size){
    //token.resize(tIndex+1);
    token.resize(size);
    //for(int i=0; i<tIndex+1; i++){
    for(int i=0; i<size; i++){
        token[i].resize(4);
        for(int j=0; j<(int)token[i].size(); j++){
            token[i][j].resize(3);
        }
    }
}

void Construction::selectToken(QString constructId){
    int index = 0;
    int size = 0;
    QSqlQuery query;
    if(query.exec("select count(ax) from "+Db::constructsTable+" where name= "+constructId)) std::cout<<"distinct token parts selected"<<std::endl;
    else qDebug()<<"select distinct token parts error"<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        size = query.value(0).toInt();
    }
    initToken(size);
    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b FROM "+Db::constructsTable+" WHERE name="+constructId+"")) std::cout<<"token selected"<<std::endl;
    else qDebug()<<"select token error"<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        token[index][0][0] = query.value(0).toFloat();
        token[index][0][1] = query.value(1).toFloat();
        token[index][0][2] = query.value(2).toFloat();

        token[index][1][0] = query.value(3).toFloat();
        token[index][1][1] = query.value(4).toFloat();
        token[index][1][2] = query.value(5).toFloat();

        token[index][2][0] = query.value(6).toFloat();
        token[index][2][1] = query.value(7).toFloat();
        token[index][2][2] = query.value(8).toFloat();

        token[index][3][0] = query.value(9).toFloat();
        token[index][3][1] = query.value(10).toFloat();
        token[index][3][2] = query.value(11).toFloat();
        index++;
    }
}

/*void Construction::setToken(int i, std::vector<std::vector<std::vector<float>>> &construct){
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

void Construction::wireToken(std::vector<std::vector<std::vector<float>>> token, int x, int z, float offX, float offZ, std::vector<std::vector<std::vector<int>>> &mapTiles){
    float clip = 0.5;
    for(int i=0; i<(int)token.size(); i++){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(!mapTiles[x][z][1]){
        World::validPlace = false;
        glColor3f(1,0,0);
    }
    else{
        World::validPlace = true;
        glColor3f(0.9,0.9,0.9);
    }
    glBegin(GL_POLYGON);
        glVertex3f(offX+clip+x+token[i][0][0], token[i][0][1], offZ+clip+z+token[i][0][2]);
        glVertex3f(offX+clip+x+token[i][1][0], token[i][1][1], offZ+clip+z+token[i][1][2]);
        glVertex3f(offX+clip+x+token[i][2][0], token[i][2][1], offZ+clip+z+token[i][2][2]);
        glVertex3f(offX+clip+x+token[i][3][0], token[i][3][1], offZ+clip+z+token[i][3][2]);
    glEnd();
    }
}
