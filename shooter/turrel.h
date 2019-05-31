#ifndef TURREL_H
#define TURREL_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>
#include <QGraphicsScene>
#include "ui_turrel.h"

#define pen(C) QPen(QColor(Qt::C))
#define br(C) QBrush(Qt::C)

class enemy :public QObject{
  Q_OBJECT
  QGraphicsScene* scene;
public:
  int myX=qrand()%400+20;
  int myY=580;
  enemy(QGraphicsScene* now){
    scene=now;
    paint();
  }
public slots:
  void paint(){
    scene->addEllipse(myX-20,myY-20,40,40,pen(blue),br(red));
  }
  void hide(){
    scene->addEllipse(myX-20,myY-20,40,40,pen(white),br(white));
  }
};

namespace Ui {
class turrel;
}

class turrel : public QMainWindow
{
    Q_OBJECT

public:
    explicit turrel(QWidget *parent = 0);
    ~turrel();
public slots:
    void keyPressEvent(QKeyEvent* ev);
signals:
    void showall();
    void hideall();
private:
    Ui::turrel *ui;
    QGraphicsScene* front= new QGraphicsScene();
    short x=20;
};

#endif // TURREL_H
