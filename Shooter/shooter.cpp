#include "shooter.h"
#include "block.h"
#include "bullet.h"
#include <fstream>
#include <QInputDialog>
#include <QProcess>

shooter::shooter(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::shooter)
{
    std::ifstream file("shooter-data");
    if(! file.is_open() ){
      file.close();
      bin::set(0,0,false);
    }
  ui->setupUi(this);
  if(bin::mazesComplete()<10)BLOCKS=10;
  else if(bin::mazesComplete()>40)BLOCKS=40;
  else BLOCKS=bin::mazesComplete();
  setFixedSize(500,600+ui->menuBar->height());
  kirpich=new block*[BLOCKS];
  for(short i=0;i<BLOCKS;i++){
      kirpich[i]=new block(i%5*100,rand()%(i+1)*50+300,rand()%9+1,this);
      connect(kirpich[i],SIGNAL(achieve(int)),this,SLOT(unlockAch(int)));
  }
  progress= new QProgressBar(this);
  progress->setRange(0,BLOCKS);
  progress->setGeometry(0,20,500,20);
  progress->setFormat("%v/%m (%p%)");
  setFocus(Qt::ActiveWindowFocusReason);
  unlockAch(bin::brokenBlocks());
}

void shooter::keyPressEvent(QKeyEvent *ev){
  switch(ev->key()){
    case Qt::Key_D://D
    case 1042://D rus
    case Qt::Key_Right:
      if(ui->tank->x()<460)
      ui->tank->move(ui->tank->x()+10,0);
    break;
    case Qt::Key_A://A
    case 1060://A rus
    case Qt::Key_Left:
      if(ui->tank->x()>0)
      ui->tank->move(ui->tank->x()-10,0);
    break;
    case Qt::Key_S:
    case 1067://S rus
    case Qt::Key_Down:{
      emit pif_paf(ui->tank->x()+20);
      bullet* some= new bullet(this);
      delete some;}
    break;
    case Qt::Key_Escape:
      exit(0);
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
  if(bin::mazesComplete()>=5)ui->actionNew_Game->setDisabled(false);
  if(bin::mazesComplete()==5){
      QMessageBox::information(this,"YaaaaY","15th maze!\nYou can restart the game any time you want!");
      bin::set(bin::brokenBlocks(),bin::mazesComplete()+1);
  }
  if(bin::mazesComplete()>=15)progress->show();
  if(bin::mazesComplete()==15)QMessageBox::information(this,"YaaaaY","You had winned 40 times!\nNow you can see you lvl progress!");
  progress->setValue(rushed);
}

void shooter::on_actionAchievements_triggered(){
    blockSignals(true);
    QMessageBox::information(this,"Achievements","Unlock -- blocks\n"
    "1.Icon   10\n"
    "2.Game menu  50\n"
    "3.Game->Pause 70\n"
    "4.Stats menu 120\n"
    "5.Stats->Progress 160\n"
    "6.Stats->Achievements 200\n"
    "7"
                                                 ".Options menu 250\n"
    "8.Options->Change bricks' style 290"
    );
    QMessageBox::information(this,"Achiewements","Unlock -- mazes\n"
    "1.Game->New game  5\n"
    "2.Options->Progress bar 15");
    blockSignals(false);
}

void shooter::on_actionProgress_triggered()
{
  blockSignals(true);
  QString text="Blocks broken:";
  text+=QString::number(bin::brokenBlocks());
  text+="\nLevels completed:";
  text+=QString::number(bin::mazesComplete());
  QMessageBox::information(this,"Your Progress:",text);
  blockSignals(false);
}

void shooter::on_actionChange_blocks_triggered()
{
    bin::set(
        bin::brokenBlocks(),
        bin::mazesComplete(),
        !bin::styleBlocks()
    );
}

void shooter::on_actionNew_Game_triggered()
{
    QProcess::startDetached(
        QApplication::arguments()[0],
        QApplication::arguments()
    );
    QApplication::exit(0);
}

void shooter::timerEvent(QTimerEvent *ev){
    Q_UNUSED(ev);
    if(windowState().testFlag(Qt::WindowActive))emit pif_paf(ui->tank->x()+20);

    for(int block=0;block<BLOCKS;block++){
        for(int i=0;i<BLOCKS;i++){
            if(i==block)continue;
            if(kirpich[block]->x()==kirpich[i]->x()&& kirpich[block]->y()==kirpich[i]->y() && kirpich[block]->x()!=-300){
                kirpich[block]->move(kirpich[block]->x()-100,kirpich[block]->y());
                if(kirpich[block]->x()>-300&&kirpich[block]->x()<0)
                    kirpich[block]->move(400,kirpich[block]->y()+50);
            }
        }
    }
}

shooter::~shooter()
{
  delete ui;
}

void shooter::on_actionPause_triggered()
{
    blockSignals(true);
    QString style=styleSheet();
    setStyleSheet("");
    QMessageBox::information(this,"Game's paused","Press OK to resume this game");
    setStyleSheet(style);
    blockSignals(false);
}
