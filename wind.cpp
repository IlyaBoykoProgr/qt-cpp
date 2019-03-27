#include "wind.h"
#include "ui_window.h"
#include <iostream>

bool X_or_O= true;
class XO{
public:
    QPushButton *myBut;
    QStatusBar *myStatus;
  void clicked(){
      if(!(myBut->text()==" "))return;
      if(X_or_O==true)this->setX();
      else this->setO();
      myBut->setDisabled(true);
  }
  void setBut(QPushButton *parent, QStatusBar *bar){
      myBut=parent; myStatus=bar;
  }
  void start(){
      myBut->setText(" ");
      myBut->setDisabled(false);
      myStatus->showMessage("Ходят Х");
  }
  void setX(){
      myBut->setText("X");
      myBut->setStyleSheet("color:red");
      myStatus->showMessage("Ходят О");
      X_or_O=!X_or_O;
  }
  void setO(){
      myBut->setText("O");
      myBut->setStyleSheet("color:blue");
      myStatus->showMessage("Ходят Х");
      X_or_O=!X_or_O;
  }
};
XO buts[9];

wind::wind(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wind)
{
    ui->setupUi(this);
    buts[0].setBut(ui->but0,ui->statusBar);
    buts[1].setBut(ui->but1,ui->statusBar);
    buts[2].setBut(ui->but2,ui->statusBar);
    buts[3].setBut(ui->but3,ui->statusBar);
    buts[4].setBut(ui->but4,ui->statusBar);
    buts[5].setBut(ui->but5,ui->statusBar);
    buts[6].setBut(ui->but6,ui->statusBar);
    buts[7].setBut(ui->but7,ui->statusBar);
    buts[8].setBut(ui->but8,ui->statusBar);
    for(int i=0; i<9; i++)connect(buts[i].myBut,SIGNAL(clicked(bool)),this,SLOT(on_but()));
}

void wind::on_but(){
    for(int i=0; i<9; i++)
        if(buts[i].myBut==sender()){
            buts[i].clicked();
            break;
        }
}

wind::~wind()
{
    delete ui;
}

void wind::on_action_triggered()
{
 for(int i=0;i<9;i++)buts[i].start();
}

void wind::paintEvent(QPaintEvent *event){
    ui->but0->setMinimumHeight(ui->but0->width());
    ui->but1->setMinimumHeight(ui->but1->width());
    ui->but2->setMinimumHeight(ui->but2->width());
    ui->but3->setMinimumHeight(ui->but3->width());
    ui->but4->setMinimumHeight(ui->but4->width());
    ui->but5->setMinimumHeight(ui->but5->width());
    ui->but6->setMinimumHeight(ui->but6->width());
    ui->but7->setMinimumHeight(ui->but7->width());
    ui->but8->setMinimumHeight(ui->but8->width());
    this->resize(this->width(),this->width());
}
