#include "shooter.h"
#include "block.h"
#include "bullet.h"
#include <fstream>
#include <QInputDialog>
#include <QApplication>
#include <QPushButton>

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
      ui->tank->move(ui->tank->x()+10,0);
    break;

    case 65://A
    case 1060://A rus
    case Qt::Key_Left:
      if(ui->tank->x()>0)
      ui->tank->move(ui->tank->x()-10,0);
    break;
    case 32:
    case Qt::Key_Down:
      emit pif_paf(ui->tank->x()+20);
      bullet* some= new bullet(this);
      delete some;
    break;
  }
}

void shooter::unlockAch(int broken){
  if(broken>=10)setWindowIcon(QIcon(":/icons/icon1.jpg"));
  if(broken==10)QMessageBox::information(this,"YaaaaY","You have just broken 10th block!\nNow you can see window icon!");
  if(broken>=50)ui->menuGame->setDisabled(false);
  if(broken==50)QMessageBox::information(this,"YaaaaY","You have just broken 50th block!\nMenu Game is unlocked!");
  if(broken>=70)ui->actionPause->setDisabled(false);
  if(broken==70)QMessageBox::information(this,"YaaaaY","70th block!\nNow you can pause the game at the menu!");
  if(broken>=120)ui->menuStats->setDisabled(false);
  if(broken==120)QMessageBox::information(this,"YaaaaY","120th block!\nMenu Stats is unlocked!");
  if(broken>=160)ui->actionProgress->setDisabled(false);
  if(broken==160)QMessageBox::information(this,"YaaaaY","160th block!\nYou can see your progress!");
  if(broken>=200)ui->actionAchievements->setDisabled(false);
  if(broken==200)QMessageBox::information(this,"YaaaaY","200th block!\nYou can see all achievements at the menu!");
  if(broken>=250)ui->menuOptions->setDisabled(false);
  if(broken==250)QMessageBox::information(this,"YaaaaY","250th block!\nMenu Options is unloked!");
  if(broken>=290)ui->actionChange_blocks->setDisabled(false);
  if(broken==290)QMessageBox::information(this,"YaaaaY","290th block!\nSome option added...");
  if(bin::mazesComplete()>=15)ui->actionNew_Game->setDisabled(false);
  if(bin::mazesComplete()==15)QMessageBox::information(this,"YaaaaY","15th maze!\nYou can restart the game any time you want!");
}

void shooter::on_actionAchievements_triggered()
{
    QMessageBox::information(this,"Achievements","Unlock -- blocks\n"
    "1.Icon   10\n"
    "2.Game menu  50\n"
    "3.Game->Pause 70\n"
    "4.Stats menu 120\n"
    "5.Stats->Pogress 160\n"
    "6.Stats->Achievements 200"
    "7.Options menu 250\n"
    "8.Options->Change bricks' style 290"
    );
    QMessageBox::information(this,"Achiewements","Unlock -- mazes\n"
    "1.Game->New game  15\n");
}

void shooter::on_actionProgress_triggered()
{
  QString text="Blocks broken:";
  text+=QString::number(bin::brokenBlocks());
  text+="\nLevels completed:";
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
    QMessageBox::information(this,"All","OK.\nPress OK");
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

void shooter::timerEvent(QTimerEvent *ev){
    Q_UNUSED(ev);
    emit pif_paf(ui->tank->x()+20);
}

shooter::~shooter()
{
  delete ui;
}

void shooter::on_actionQuit_triggered()
{
    QApplication::exit(123);
}

void shooter::on_actionPause_triggered()
{
    blockSignals(true);
    QMessageBox::information(this,"Game's paused","Press OK to resume this game");
    blockSignals(false);
}
