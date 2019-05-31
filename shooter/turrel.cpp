#include "turrel.h"
#include "ui_turrel.h"

turrel::turrel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::turrel)
{
    ui->setupUi(this);
    setAnimated(true);
    ui->scene->setFixedSize(530,630);
    ui->scene->setScene(front);
    front->addRect(0,0,500,600,pen(white));
    connect(this,SIGNAL(showall()),SLOT(keyPressEvent(QKeyEvent*)));
    enemy monster(front);
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
      QLabel pula(this);pula.setStyleSheet("background:yellow");
      pula.resize(12,20);
      for(short y=70;y<600;y+=5){
          pula.move(x+20,y);
          pula.show();repaint();
      }
    break;
    }
    front->addRect(x-20,0,40,30,pen(black),br(red));
    front->addEllipse(x-6,10,12,30,pen(black),br(green));
}

turrel::~turrel()
{
    delete ui;
}
