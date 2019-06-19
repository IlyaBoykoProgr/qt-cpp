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
  Ui::shooter *ui;
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
     FILE *f; //описываем файловую переменную
     int n=0;
     //открываем существующий двоичный файл в режиме чтения
     f=fopen("shooter-data", "rb");
     if(f==NULL){
      fclose(f);
      f=fopen("shooter-data", "wb");
      fwrite(&n, sizeof(int), 1, f);
      fclose(f);
      f=fopen("shooter-data", "rb");
     }
     //считываем из файла одно целое число в переменную n
     fread(&n, sizeof(int), 1, f);
     fclose(f);
     //создаем двоичный файл в режиме записи
     f=fopen("shooter-data", "wb");
     n++;
     fwrite(&n, sizeof(int), 1, f);
     fclose(f);
     ((shooter*)parent())->rushed++;
     emit message(QString::number(n)+" blocks broken. "+QString::number(((shooter*)parent())->rushed)+" blocks broken this game",300);
     if(n>=50){((shooter*)parent())->setWindowIcon(QIcon(":/images/icon.jpg"));}
     if(n==50)QMessageBox::information(this,"YaaaaY","You have just broken 100th block!\nNow you can see window icon!");
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
      if(QMessageBox::question(par,"Lose","GAME OVER",QMessageBox::Retry,QMessageBox::Ok)
           ==QMessageBox::Retry){
        system((par->progPath+"&").toLocal8Bit().data());
      }
      exit(0);
    }
  }
signals:
  void message(QString,int);
};

#endif // SHOOTER_H
