#ifndef FIELD_H
#define FIELD_H
#include <math.h>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

enum Cell{
  CL_NONE, CL_BOAT, CL_MISS, CL_DESTROYED
};

class Field:public QWidget{
    Q_OBJECT
    QWidget boats[10][10];
public:
    bool clickable=true;
    int clickX, clickY;
    Field(QWidget* parent,int newX,int newY):QWidget(parent){
        setGeometry(newX,newY,220,220);
        for(int x=0;x<10;x++)for(int y=0;y<10;y++){
            boats[x][y].setGeometry(x*21,y*21,21,21);
            boats[x][y].setParent(this);
            boats[x][y].show();
            setBoat(x,y,CL_NONE);
        }
    }
    void mousePressEvent(QMouseEvent* event){
        clickX=event->x()+5;clickY=event->y()+5;
        clickX= floor(clickX/22.0);
        clickY= floor(clickY/22.0);
        emit clicked();
        if(!clickable)return;
        setBoat(clickX,clickY,isEmpty(clickX,clickY)?CL_BOAT:CL_NONE);
    }
    void setBoat(int x, int y, Cell exist){
        switch(exist){
        case CL_NONE:
            boats[x][y].setStyleSheet(" ");
            break;
        case CL_BOAT:
            boats[x][y].setStyleSheet("background-image:url(:/images/boat.png)");
            break;
        case CL_MISS:
            boats[x][y].setStyleSheet("background-image:url(:/images/miss.png)");
            break;
        case CL_DESTROYED:
            boats[x][y].setStyleSheet("background:red");
            break;
        }
    }
    bool isABoat(int x, int y){
        return boats[x][y].styleSheet()=="background-image:url(:/images/boat.png)" ||
               boats[x][y].styleSheet()=="background:red";
    }
    bool isEmpty(int x, int y){
        return boats[x][y].styleSheet()==" ";
    }
    QString getCode(){
        QString code="";
        for(int x=0;x<10;x++)for(int y=0;y<10;y++){
            code+=QString::number(isABoat(x,y));
        }
        return code;
    }
signals:
    void clicked();
};

#endif // FIELD_H
