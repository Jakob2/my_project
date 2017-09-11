#include "field.h"


std::vector<int> Field::fieldSet;
std::vector<std::vector<std::vector<float>>> Field::field;

Field::Field(){
    setField(1);
}

void Field::setField(int size){
    Field::field.clear();
    for(int i=0; i<size; i++){
        Field::field.push_back(std::vector<std::vector<float>>());
        for(int j=0; j<7; j++){
            Field::field[i].push_back(std::vector<float>());
            for(int k=0; k<3; k++){
                Field::field[i][j].push_back(0);
            }
        }
    }
}


/*void Field::selectFieldSet(){
    QSqlQuery query;
    Field::fieldSet.clear();
    if(query.exec("SELECT DISTINCT name FROM "+constructsTable+" WHERE field = 1")) std::cout<<"fieldset selected"<<std::endl;
    else qDebug()<<"select fieldset error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Field::fieldSet.push_back(query.value(0).toInt());
    }
}*/

void Field::selectField(QString name){
    Field::field.clear();
    setField(1);
    int index, range;
    index = 0;
    QSqlQuery query;
    if(query.exec("SELECT COUNT(*) FROM "+Db::constructsTable+" WHERE name="+name+"")) std::cout<<"field range selected"<<std::endl;
    else qDebug()<<"field range error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()) range = query.value(0).toInt();
    setField(range);

    if(query.exec("SELECT ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b FROM "+Db::constructsTable+" WHERE name="+name+"")) std::cout<<"field selected"<<std::endl;
    else qDebug()<<"select field error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Field::field[index][0][0] = query.value(0).toFloat();
        Field::field[index][0][1] = query.value(1).toFloat();
        Field::field[index][0][2] = query.value(2).toFloat();

        Field::field[index][1][0] = query.value(3).toFloat();
        Field::field[index][1][1] = query.value(4).toFloat();
        Field::field[index][1][2] = query.value(5).toFloat();

        Field::field[index][2][0] = query.value(6).toFloat();
        Field::field[index][2][1] = query.value(7).toFloat();
        Field::field[index][2][2] = query.value(8).toFloat();

        Field::field[index][3][0] = query.value(9).toFloat();
        Field::field[index][3][1] = query.value(10).toFloat();
        Field::field[index][3][2] = query.value(11).toFloat();

        Field::field[index][4][0] = query.value(12).toFloat();
        Field::field[index][4][1] = query.value(13).toFloat();
        Field::field[index][4][2] = query.value(14).toFloat();
        index++;
    }
}

void Field::insertFieldPart(QString map, QString name, std::vector<std::vector<std::vector<float>>> &field, int xLow, int xHigh, int zLow, int zHigh){
    //if(World::areaX<World::tile[2] && World::areaZ<World::tile[3]){
    if(fieldstuff.areaX<World::map.tile[2] && fieldstuff.areaZ<World::map.tile[3]){
        for(int x=xLow; x<=xHigh; x++){
            for(int z=zLow; z<=zHigh; z++){
                if(fieldValidation(x, z)){
                    fieldSQL(map, name, field, x,z);
                    Db::updateOpen(QString::number(x-1), QString::number(z-1), QString::number(0));
                    std::cout<<"FIELD I"<<std::endl;
                }
            }
        }
    }
    //else if(World::areaX>World::tile[2] && World::areaZ<World::tile[3]){
    else if(fieldstuff.areaX>World::map.tile[2] && fieldstuff.areaZ<World::map.tile[3]){
        for(int x=xHigh; x<=xLow; x++){
           for(int z=zLow; z<=zHigh; z++){
               if(fieldValidation(x, z)){
                    fieldSQL(map, name, field, x,z);
                    Db::updateOpen(QString::number(x-1), QString::number(z-1), QString::number(0));
                    std::cout<<"FIELD II"<<std::endl;
                }
            }
        }
    }
    //else if(World::areaX>World::tile[2] && World::areaZ>World::tile[3]){
    else if(fieldstuff.areaX>World::map.tile[2] && fieldstuff.areaZ>World::map.tile[3]){
        for(int x=xHigh; x<=xLow; x++){
            for(int z=zHigh; z<=zLow; z++){
                if(fieldValidation(x, z)){
                    fieldSQL(map, name, field, x,z);
                    Db::updateOpen(QString::number(x-1), QString::number(z-1), QString::number(0));
                    std::cout<<"FIELD III"<<std::endl;
                }
            }
        }
    }
    //else if(World::areaX<World::tile[2] && (World::areaZ>World::tile[3])){
    else if(fieldstuff.areaX<World::map.tile[2] && (fieldstuff.areaZ>World::map.tile[3])){
        for(int x=xLow; x<=xHigh; x++){
            for(int z=zHigh; z<=zLow; z++){
                if(fieldValidation(x, z)){
                    fieldSQL(map, name, field, x,z);
                    Db::updateOpen(QString::number(x-1), QString::number(z-1), QString::number(0));
                    std::cout<<"FIELD IV"<<std::endl;
                }
            }
        }
    }
}

void Field::fieldarea(std::vector<std::vector<std::vector<float>>> &field, float xPos, float zPos){
    float r,g,b;
    r = field[1][4][0];
    g = field[1][4][1];
    b = field[1][4][2];

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glColor3f(r,g,b);
    for(int f=0; f<(int)field.size(); f++){
        //if(World::tile[2] > World::areaX && World::tile[3] > World::areaZ)
        if(World::map.tile[2] > fieldstuff.areaX && World::map.tile[3] > fieldstuff.areaZ)
            southarea(field, f, xPos,zPos);
        //else if(World::tile[2] < World::areaX && World::tile[3] > World::areaZ)
        else if(World::map.tile[2] < fieldstuff.areaX && World::map.tile[3] > fieldstuff.areaZ)
            westarea(field, f, xPos,zPos);
        //else if(World::tile[2] > World::areaX && World::tile[3] < World::areaZ)
        else if(World::map.tile[2] > fieldstuff.areaX && World::map.tile[3] < fieldstuff.areaZ)
            eastarea(field, f, xPos,zPos);
        //else if(World::tile[2] < World::areaX && World::tile[3] < World::areaZ)
        else if(World::map.tile[2] < fieldstuff.areaX && World::map.tile[3] < fieldstuff.areaZ)
            northarea(field, f, xPos,zPos);
    }
    glPopMatrix();
}

void Field::southarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos){
    float x, z;
    //for(int i=floor(World::areaX-xPos); i<ceil(World::tile[2]-xPos); i++){
    for(int i=floor(fieldstuff.areaX-xPos); i<ceil(World::map.tile[2]-xPos); i++){
        x=i+0.5;
        //for(int j=floor(World::areaZ-zPos); j<ceil(World::tile[3]-zPos); j++){
        for(int j=floor(fieldstuff.areaZ-zPos); j<ceil(World::map.tile[3]-zPos); j++){
            z=j+0.5;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(2.0);
            Shape::corpus(field,f, x,0,z, xPos,zPos);
            glEnd();
        }
    }
}

void Field::westarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos){
    float x, z;
    //for(int i=floor(World::tile[2]-xPos); i<ceil(World::areaX-xPos); i++){
    for(int i=floor(World::map.tile[2]-xPos); i<ceil(fieldstuff.areaX-xPos); i++){
        x=i+0.5;
        //for(int j=floor(World::areaZ-zPos); j<ceil(World::tile[3]-zPos); j++){
        for(int j=floor(fieldstuff.areaZ-zPos); j<ceil(World::map.tile[3]-zPos); j++){
            z=j+0.5;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(2.0);
            Shape::corpus(field,f, x,0,z, xPos,zPos);
            glEnd();
        }
    }
}

void Field::northarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos){
    float x, z;
    //for(int i=floor(World::tile[2]-xPos); i<ceil(World::areaX-xPos); i++){
    for(int i=floor(World::map.tile[2]-xPos); i<ceil(fieldstuff.areaX-xPos); i++){
        x=i+0.5;
        //for(int j=floor(World::tile[3]-zPos); j<ceil(World::areaZ-zPos); j++){
        for(int j=floor(World::map.tile[3]-zPos); j<ceil(fieldstuff.areaZ-zPos); j++){z=j+0.5;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(2.0);
            Shape::corpus(field,f, x,0,z, xPos,zPos);
            glEnd();
        }
    }
}

void Field::eastarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos){
    float x, z;
    //for(int i=floor(World::areaX-xPos); i<ceil(World::tile[2]-xPos); i++){
    for(int i=floor(fieldstuff.areaX-xPos); i<ceil(World::map.tile[2]-xPos); i++){
        x=i+0.5;
        //for(int j=floor(World::tile[3]-zPos); j<ceil(World::areaZ-zPos); j++){
        for(int j=floor(World::map.tile[3]-zPos); j<ceil(fieldstuff.areaZ-zPos); j++){
            z=j+0.5;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(2.0);
            Shape::corpus(field,f, x,0,z, xPos,zPos);
            glEnd();
        }
    }
}

void Field::fieldSQL(QString map, QString name, std::vector<std::vector<std::vector<float>>> &field, int x, int z){
    QSqlQuery query;
    QString mid, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b;
    mid = id();
    for(int index=0; index<(int)field.size(); index++){
        ax = QString::number(field[index][0][0]);
        ay = QString::number(field[index][0][1]);
        az = QString::number(field[index][0][2]);

        bx = QString::number(field[index][1][0]);
        by = QString::number(field[index][1][1]);
        bz = QString::number(field[index][1][2]);

        cx = QString::number(field[index][2][0]);
        cy = QString::number(field[index][2][1]);
        cz = QString::number(field[index][2][2]);

        dx = QString::number(field[index][3][0]);
        dy = QString::number(field[index][3][1]);
        dz = QString::number(field[index][3][2]);

        r = QString::number(field[index][4][0]);
        g = QString::number(field[index][4][1]);
        b = QString::number(field[index][4][2]);

        //cout<<"x: "<<x<<" / z: "<<z<<endl;
        //query.exec("INSERT INTO "+Db::mapTable+" (id, map, name, x,y,z, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b) VALUES ("+mid+", "+map+", "+name+", "+QString::number(x)+",0,"+QString::number(z)+", "+ax+","+ay+","+az+", "+bx+","+by+","+bz+", "+cx+","+cy+","+cz+", "+dx+","+dy+","+dz+", "+r+","+g+","+b+" )");
        if(query.exec("INSERT INTO "+Db::mapTable+" (id, map, name, x,y,z, ax,ay,az, bx,by,bz, cx,cy,cz, dx,dy,dz, r,g,b) VALUES ("+mid+", "+map+", "+name+", "+QString::number(x)+",0,"+QString::number(z)+", "+ax+","+ay+","+az+", "+bx+","+by+","+bz+", "+cx+","+cy+","+cz+", "+dx+","+dy+","+dz+", "+r+","+g+","+b+" )")) std::cout<<"field inserted"<<std::endl;
        else qDebug()<<"insert field error: "<<query.lastError()<<" / "<<query.lastQuery();
    }
}

int Field::fieldValidation(int x, int z){
    int open = 1;
    QSqlQuery query;
    if(query.exec("SELECT open FROM "+Db::tilesTable+" WHERE x="+QString::number(x-1)+" AND z="+QString::number(z-1)+"")) std::cout<<"field open selected"<<std::endl;
    else qDebug()<<"select field open error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
       if(!query.value(0).toInt()) open = 0;
    }
    std::cout<<"-------FIELD VALIDATION: "<<open<<std::endl;
    return open;

}

QString Field::id(){
    int id = 0;
    QSqlQuery query;
    if(query.exec("SELECT MAX(id) FROM "+Db::mapTable+"")) std::cout<<"max id selected"<<std::endl;
    else qDebug()<<"select max id error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()) id = query.value(0).toInt();
    return QString::number(id+1);
}
