#include "shooter.h"
#include "block.h"
#include "ui_shooter.h"
#include <fstream>
#include <QInputDialog>
#include <QApplication>
#include <QPushButton>
int BLOCKS;

shooter::shooter(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::shooter)
{
    std::ifstream is("shooter-data");
    if(! is.is_open() ){
      is.close();
      bin::set(0,0,false);
    }
  ui->setupUi(this);
  BLOCKS=QInputDialog::getInt(this,"Difficulty","How many blocks do you want to break?",30,10);
  setFixedSize(500,600+ui->menuBar->height());
  connect(this,SIGNAL(pif_paf(int)),this,SLOT(shoot(int)));
  kirpich=new block*[BLOCKS];
  for(short i=0;i<BLOCKS;i++){
      kirpich[i]=new block(i%5*100,rand()%(i+1)*50+300,rand()%9+1,this);
      connect(kirpich[i],SIGNAL(achieve(int)),this,SLOT(unlockAch(int)));
  }
  unlockAch(bin::brokenBlocks());
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
  for(short i=40;i<620;i+=10){
      pula.move(x-3,i);
      repaint();
      for(short k=0;k<BLOCKS;k++)
        if( (kirpich[k]->y()==i ||kirpich[k]->y()==i-5) && kirpich[k]->x()<x && kirpich[k]->x()+100>x)
          {kirpich[k]->destroy();i=620;break;}
  }
  if(rushed>=BLOCKS){
      QMessageBox::information(this,"You won!","You already broke all\n"+QString::number(BLOCKS)+" BLOCKS!!!");
      bin::set(bin::brokenBlocks(), bin::mazesComplete()+1);
      on_actionNew_Game_triggered();
  }
}

void shooter::unlockAch(int broken){
  if(broken>=10)setWindowIcon(QIcon(":/icons/icon1.jpg"));
  if(broken==10)QMessageBox::information(this,"YaaaaY","You have just broken 10th block!\nNow you can see window icon!");
  if(broken>=50)ui->menuGame->setDisabled(false);
  if(broken==50)QMessageBox::information(this,"YaaaaY","You have just broken 50th block!\nMenu Game is unlocked!");
  if(broken>=70)ui->actionAchievements->setDisabled(false);
  if(broken==70)QMessageBox::information(this,"YaaaaY","70th block!\nNow you can see all achievements at the menu!");
  if(broken>=120)ui->actionProgress->setDisabled(false);
  if(broken==120)QMessageBox::information(this,"YaaaaY","120th block!\nNow you can see your progress at the menu!");
  if(broken>=160)ui->menuOptions->setDisabled(false);
  if(broken==160)QMessageBox::information(this,"YaaaaY","160th block!\nMenu Options is unlocked!");
  if(broken>=220)ui->actionChange_blocks->setDisabled(false);
  if(broken==220)QMessageBox::information(this,"YaaaaY","220th block!\nYou can change style of bricks!");
  if(bin::mazesComplete()>=15)ui->actionNew_Game->setDisabled(false);
}

void shooter::on_actionAchievements_triggered()
{
    QMessageBox::information(this,"Achievements","Unlock -- blocks\n"
    "1.Icon   10\n"
    "2.Game menu  50\n"
    "3.Game->Achievements 70\n"
    "4.Game->Progress 120\n"
    "5.Options menu 160\n"
    "6.Options->Change brick's style 220"
    );
    QMessageBox::information(this,"Achiewements","Unlock -- mazes\n"
    "1.Game->New game  15\n");
}

void shooter::on_actionProgress_triggered()
{
  QString text="Blocks broken:";
  text+=QString::number(bin::brokenBlocks());
  text+="\nLevels complete:";
  text+=QString::number(bin::mazesComplete());
  QMessageBox::information(this,"Your Progress:",text);
}

void shooter::on_actionChange_blocks_triggered()
{
    bin::set(
        bin::brokenBlocks(),
        bin::mazesComplete(),
        !bin::styleBlocks()
    );
    QMessageBox::information(this,"All","is OK.\nPress OK");
}

#include <QProcess>
void shooter::on_actionNew_Game_triggered()
{
    QProcess::startDetached(
        QApplication::arguments()[0],
        QApplication::arguments()
    );
    QApplication::exit();
}

shooter::~shooter()
{
  delete ui;
}

void shooter::on_actionQuit_triggered()
{
    QApplication::exit(123);
}
