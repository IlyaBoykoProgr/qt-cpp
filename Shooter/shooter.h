#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  Ui::shooter *ui;
  short rushed=0;
  explicit shooter(QWidget *parent = 0);
  ~shooter();
  void keyPressEvent(QKeyEvent* ev);

public slots:
  void shoot(int x);
  void unlockAch(int broken);
signals:
  void pif_paf(int x);
private slots:
  void on_actionAchievements_triggered();

  void on_actionProgress_triggered();

  void on_actionChange_blocks_triggered();
public slots:
  void on_actionNew_Game_triggered();

private:
  block** kirpich;
};



#include "database.h"
class block: public QLabel{
  Q_OBJECT
  short h;
public:
  block(int x, int y,short health,shooter* parent){
    setParent(parent);
    connect(parent,SIGNAL(pif_paf(int)),this,SLOT(update()));
    setGeometry(x+3,y,94,40);
    show();
    h=health+1;
    destroy();
  }
  void destroy(){
    if(h<1){
     move(-200,0);
     bin::set(bin::brokenBlocks()+1);
     ((shooter*)parent())->rushed++;
     emit achieve(bin::brokenBlocks());
    }else{
    h--;
    setNum(h);
    if(bin::styleBlocks())
        setStyleSheet("background:#B30;border:"+QString::number(9-h)+"px solid #555;");
    else
        setStyleSheet("background:rgba(255,"+QString::number(h*20)+",0,230);border:4px solid #666;");
    }
  }
public slots:
  void update(){
    move(x(),y()-5);
    if(this->y()<45&& this->x()> -200){
        shooter* par=((shooter*)parent());
      if(QMessageBox::question(par,"Lose","GAME OVER",QMessageBox::Retry,QMessageBox::Ok)
           ==QMessageBox::Retry){
          par->on_actionNew_Game_triggered();
      }
      exit(0);
    }
  }
signals:
  void achieve(int);
};

#endif // SHOOTER_H
