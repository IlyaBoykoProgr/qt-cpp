#include "turrel.h"
#include "ui_turrel.h"
#define pen(C) QPen(QColor(Qt::C))
#define br(C) QBrush(Qt::C)

turrel::turrel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::turrel)
{
    ui->setupUi(this);
    setAnimated(true);
    ui->scene->setFixedSize(530,630);
    ui->scene->setScene(front);
    front->addRect(0,0,500,600,pen(white));
}

void turrel::keyPressEvent(QKeyEvent* ev){
    front->addRect(x-20,0,40,40,pen(white),br(white));
    switch(ev->key()){
    case 68://D
      (x>479)? x=480 : x+=5;
    break;
    case 65://A
      (x<21)? x=20 : x-=5;
    break;
    case 32://space
      for(short y=40;y<580;y++){
          front->addLine(x,y,x,y+30,pen(yellow));
          front->addLine(x,y,x,y+30,pen(white));
      }
    break;
    }
    front->addRect(x-20,0,40,30,pen(black),br(red));
    front->addRect(x-5,10,10,30,pen(black),br(green));
}

turrel::~turrel()
{
    delete ui;
}
