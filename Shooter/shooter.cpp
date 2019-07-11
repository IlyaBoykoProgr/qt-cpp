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
    case Qt::Key_Down:
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
      FILE *f; //описываем файловую переменную
      int n=0, c=0;
      //открываем существующий двоичный файл в режиме чтения
      f=fopen("shooter-data", "rb");
      //считываем из файла одно целое число в переменную n
      fread(&n, sizeof(int), 1, f);
      //считываем из файла одно целое число в переменную c
      fread(&c, sizeof(int), 1, f);
      fclose(f);
      //создаем двоичный файл в режиме записи
      f=fopen("shooter-data", "wb");
      c++;
      fwrite(&n, sizeof(int), 1, f);
      fwrite(&c, sizeof(int), 1, f);
      fclose(f);
      system("sleep 1");
      system((progPath+"&").toLocal8Bit().data());
      exit(0);
  }
}

void shooter::unlockAch(int broken){
  if(broken>=10)setWindowIcon(QIcon(":/images/icon.jpg"));
  if(broken==10)QMessageBox::information(this,"YaaaaY","You have just broken 10th block!\nNow you can see window icon!");
  if(broken>=50)ui->menuGame->setDisabled(false);
  if(broken==50)QMessageBox::information(this,"YaaaaY","You have just broken 50th block!\nMenu Game is unlocked!");
  if(broken>=100)ui->actionAchievements->setDisabled(false);
  if(broken==100)QMessageBox::information(this,"YaaaaY","100th block!\nNow you can see all achievements at the menu!");
  if(broken>=140)ui->actionProgress->setDisabled(false);
  if(broken==140)QMessageBox::information(this,"YaaaaY","140th block!\nNow you can see your progress at the menu!");
}

shooter::~shooter()
{
  delete ui;
}

void shooter::on_actionAchievements_triggered()
{
    QMessageBox::information(this,"Achievements","Prize   -- price\n"
    "1.Icon   10\n"
    "2.Game menu  50\n"
    "3.Game->Achievements 100\n"
    "4.Game->Progress 140\n");
}

void shooter::on_actionProgress_triggered()
{
  int n=0, c=0;
  FILE *f;
  //открываем существующий двоичный файл в режиме чтения
  f=fopen("shooter-data", "rb");
  //считываем из файла одно целое число в переменную n
  fread(&n, sizeof(int), 1, f);
  //считываем из файла одно целое число в переменную c
  fread(&c, sizeof(int), 1, f);
  fclose(f);
  QMessageBox::information(this,"Your Progress:","Blocks broken:"+QString::number(n)+"\nLevels complete:"+c);
}
