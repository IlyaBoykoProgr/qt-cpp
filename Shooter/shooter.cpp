#include "shooter.h"
#include "ui_shooter.h"

shooter::shooter(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::shooter)
{
  ui->setupUi(this);
  setFixedSize(500,600);
  connect(this,SIGNAL(pif_paf(int)),this,SLOT(shoot(int)));
}

void shooter::keyPressEvent(QKeyEvent *ev){
  switch(ev->key()){
    case 68://D
    case 1042://D rus
    case Qt::Key_Right:
      if(ui->tank->x()<460)
      ui->tank->move(ui->tank->x()+6,0);
    break;

    case 65://A
    case 1060://A rus
    case Qt::Key_Left:
      if(ui->tank->x()>0)
      ui->tank->move(ui->tank->x()-6,0);
    break;
    case 32:
      emit pif_paf(ui->tank->x()+20);
    break;
  }
}

void shooter::shoot(int x){
  QLabel pula(this);
  pula.setGeometry(x-3,40,6,20);
  pula.show(); pula.setStyleSheet("background:yellow;");
  for(short i=40;i<560;i+=5){
      pula.move(x-3,i);
      repaint();
  }
}

shooter::~shooter()
{
  delete ui;
}
