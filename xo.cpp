#include "xo.h"

XO::XO(QObject *parent) : QObject(parent)
{}
void XO::clicked(){
      if(!(myBut->text()==" "))return;
      if(myStatus->currentMessage()=="Ходят Х")this->setX();
      else this->setO();
      myBut->setDisabled(true);
}
void XO::setBut(QPushButton *parent, QStatusBar *bar){
      myBut=parent; myStatus=bar;
      connect(myBut,SIGNAL(clicked(bool)),this,SLOT(clicked()));
      start();
}
void XO::start(){
      myBut->setText(" ");
      myBut->setDisabled(false);
      myStatus->showMessage("Ходят Х");
}
void XO::setX(){
      myBut->setText("X");
      myBut->setStyleSheet("color:red");
      myStatus->showMessage("Ходят О");
}
void XO::setO(){
      myBut->setText("O");
      myBut->setStyleSheet("color:blue");
      myStatus->showMessage("Ходят Х");
}
