#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>

namespace Ui {
  class shooter;
}

class block: public QLabel{
  Q_OBJECT
  short h;
public:
  block(int x, int y,int health,QWidget* parent){
    setParent(parent);
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
};

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

#endif // SHOOTER_H
