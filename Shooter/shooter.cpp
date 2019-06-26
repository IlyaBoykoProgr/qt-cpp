#include "shooter.h"
#include "ui_shooter.h"
#include <QInputDialog>
int BLOCKS;

shooter::shooter(QString programm,QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::shooter)
{
  ui->setupUi(this);
  BLOCKS=QInputDialog::getInt(this,"Difficulty","How many blocks do you want to break?",30,10);
  setFixedSize(500,600+ui->statusBar->height()+ui->menuBar->height());
  connect(this,SIGNAL(pif_paf(int)),this,SLOT(shoot(int)));
  progPath=programm;
  kirpich=new block*[BLOCKS];
  for(short i=0;i<BLOCKS;i++){
      kirpich[i]=new block(i%5*100,rand()%(i+1)*50+300,rand()%9+1,this);
      connect(kirpich[i],SIGNAL(message(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
      connect(kirpich[i],SIGNAL(achieve(int)),this,SLOT(unlockAch(int)));
  }
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
  pula.show(); pula.setStyleSheet("background:yellow");
  for(short i=40;i<590;i+=10){
      pula.move(x-3,i);
      repaint();
      for(short k=0;k<BLOCKS;k++)
        if( (kirpich[k]->y()==i ||kirpich[k]->y()==i-5) && kirpich[k]->x()<x && kirpich[k]->x()+100>x)
          {kirpich[k]->destroy();i=590;break;}
  }
  if(rushed>=BLOCKS){
      QMessageBox::information(this,"You won!","You already broke all\n"+QString::number(BLOCKS)+" BLOCKS!!!");
      system("sleep 2");
      system((progPath+"&").toLocal8Bit().data());
      exit(0);
  }
}

void shooter::unlockAch(int broken){
  if(broken>=50)setWindowIcon(QIcon(":/images/icon.jpg"));
  if(broken==50)QMessageBox::information(this,"YaaaaY","You have just broken 50th block!\nNow you can see window icon!");
  if(broken>=100)ui->menuGame->setDisabled(false);
  if(broken==100)QMessageBox::information(this,"YaaaaY","You have just broken 100th block!\nMenu Game is unlocked!");
  if(broken>=130)ui->actionAchievements->setDisabled(false);
  if(broken==130)QMessageBox::information(this,"YaaaaY","130th block!\nNow you can see all achievements in the menu!");
}

shooter::~shooter()
{
  delete ui;
}

void shooter::on_actionAchievements_triggered()
{
    QMessageBox::information(this,"Achievements","What   -- blocks\n"
    "1.Icon   50\n"
    "2.Game menu  100\n"
    "3.Game->Achievements 130\n");
}
