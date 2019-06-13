#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>

class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  QString progPath;
  short rushed=0;
  explicit shooter(QString programm,QWidget *parent = 0);
  ~shooter();
  void keyPressEvent(QKeyEvent* ev);

public slots:
  void shoot(int x);
signals:
  void pif_paf(int x);
private:
  Ui::shooter *ui;
  block** kirpich;
};

class block: public QLabel{
  Q_OBJECT
  short h;
public:
  block(int x, int y,int health,shooter* parent){
    setParent(parent);
    connect(parent,SIGNAL(pif_paf(int)),this,SLOT(update()));
    setGeometry(x+3,y,94,40);
    show();
    h=health+1;
    destroy();
  }
  void destroy(){
    if(h<1){
     move(-200,1000);
     ((shooter*)parent())->rushed++;
    }else{
    h--;
    setNum(h);
    setStyleSheet("background:rgba(255,"+QString::number(h*20)+",0,230);border:4px solid #666;");
    }
  }
public slots:
  void update(){
    move(x(),y()-5);
    if(this->y()<45){
        shooter* par=((shooter*)parent());
        QMessageBox::critical(par,"Lose","GAME OVER");
        system((par->progPath+"&").toLocal8Bit().data());
        exit(0);
    }
  }
};

#endif // SHOOTER_H
