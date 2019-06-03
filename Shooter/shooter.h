#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QProgressBar>

class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  QString progPath;
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
  QProgressBar* heal= new QProgressBar(this);
public:
  block(int x, int y,int health,shooter* parent){
    setParent(parent);
    connect(parent,SIGNAL(pif_paf(int)),this,SLOT(update()));
    setStyleSheet("background:rgba(255,"+QString::number(heal->value()*25)+",0,230);border:4px solid #666;");
    setGeometry(x+3,y,94,40);
    show();
    h=health;
    heal->setGeometry(5,5,84,15);
    heal->setStyleSheet("QProgressBar{border:none} QProgressBar::chunk{background:green}");
    heal->setRange(0,h);heal->show();
  }
  void destroy(){
    if(h<1)move(-200,600);
    h--;
    heal->setValue(h);
    setStyleSheet("background:rgba(255,"+QString::number(heal->value()*25)+",0,240);border:4px solid #666;");
  }
public slots:
  void update(){
    move(x(),y()-5);
    if(this->y()<45){
        shooter* par=((shooter*)parent());
        setText("lose!");
        par->repaint();
        system("sleep 2");
        system((par->progPath+"&").toLocal8Bit().data());
        exit(0);
    }
  }
};

#endif // SHOOTER_H
