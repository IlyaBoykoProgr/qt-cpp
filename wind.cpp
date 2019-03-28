#include "wind.h"
#include "ui_window.h"
#include "xo.h"
#include <QMessageBox>

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
    for(int i=0; i<9; i++){
        XO *now= &buts[i];
        connect(now,SIGNAL(butChanged()),this,SLOT(isWinner()));
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

void wind::isWinner(){
    bool x[9];
    for(int i=0; i<9; i++) x[i]=buts[i].myBut->text()=="X";
    if((x[0]&&x[1]&&x[2])||(x[0]&&x[3]&&x[6])||
       (x[3]&&x[4]&&x[5])||(x[1]&&x[4]&&x[7])||
       (x[6]&&x[7]&&x[8])||(x[2]&&x[5]&&x[8])||(x[2]&&x[4]&&x[6])||(x[0]&&x[4]&&x[8])
    )QMessageBox::information(this,"Крестики выиграли!","Поздравляю победившего!\n\n\n\n          (c)System");
    if(!((x[0]&&x[1]&&x[2])||(x[0]&&x[3]&&x[6])||
       (x[3]&&x[4]&&x[5])||(x[1]&&x[4]&&x[7])||
       (x[6]&&x[7]&&x[8])||(x[2]&&x[5]&&x[8])||(x[2]&&x[4]&&x[6])||(x[0]&&x[4]&&x[8])
    ))QMessageBox::information(this,"Нолики выиграли!","Поздравляю победившего!\n\n\n\n          (c)System");
}

void wind::paintEvent(QPaintEvent *event){
    for(int i=0; i<9; i++) buts[i].myBut->setMinimumHeight(buts[i].myBut->width());
    this->resize(this->width(),this->width());
}
