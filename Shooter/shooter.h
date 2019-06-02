#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  explicit shooter(QWidget *parent = 0);
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
    setStyleSheet("background:#F50;border:2px solid #666;");
    setGeometry(x+3,y,94,40);
    show();
    h=health;
    setNum(h);
  }
  void destroy(){
    if(h==1)move(-200,0);
    h--;
    setNum(h);
  }
public slots:
  void update(){
    move(x(),y()-5);
  }
};

#endif // SHOOTER_H
