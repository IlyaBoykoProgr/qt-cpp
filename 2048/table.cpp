#include "table.h"
#include "ui_table.h"
#include <QScreen>
#include <QMessageBox>
#include "../animate.h"

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    show();
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        myNum[c][r]= new QPushButton(this);
        myNum[c][r]->resize(80,80);
        myNum[c][r]->move(c*80,r*80);
        myNum[c][r]->show();
        setScore(0,c,r);
    }
    resize(0,0);
    QSize screen=QApplication::screens().at(0)->availableSize();
    moveWidget(this,screen.width()/2-200, screen.height()/2-200, 200);
    setFixedSize(320,360);
}

void table::setScore(int score, int col, int row){
    scores[col][row]=score;
    if(score==0){
        myNum[col][row]->setStyleSheet("");
        myNum[col][row]->setFlat(true);
        myNum[col][row]->setText("");
        return;
    }
    myNum[col][row]->setFlat(false);
    myNum[col][row]->setText(QString::number(score));
    QString backg="background:";
    switch (score){
    case 2:backg.append("red");break;
    case 4:backg.append("orange");break;
    case 8:backg.append("yellow");break;
    case 16:backg.append("lime");break;
    case 32:backg.append("green");break;
    case 64:backg.append("aqua");break;
    case 128:backg.append("blue");break;
    case 256:backg.append("purple");break;
    case 512:backg.append("qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(35, 40, 3, 255), stop:0.16 rgba(136, 106, 22, 255), stop:0.225 rgba(166, 140, 41, 255), stop:0.285 rgba(204, 181, 74, 255), stop:0.345 rgba(235, 219, 102, 255), stop:0.415 rgba(245, 236, 112, 255), stop:0.52 rgba(209, 190, 76, 255), stop:0.57 rgba(187, 156, 51, 255), stop:0.635 rgba(168, 142, 42, 255), stop:0.695 rgba(202, 174, 68, 255), stop:0.75 rgba(218, 202, 86, 255), stop:0.815 rgba(208, 187, 73, 255), stop:0.88 rgba(187, 156, 51, 255), stop:0.935 rgba(137, 108, 26, 255), stop:1 rgba(35, 40, 3, 255))");break;
    case 1024:backg.append("qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(245, 224, 176, 255), stop:0.09 rgba(246, 189, 237, 255), stop:0.14 rgba(194, 207, 246, 255), stop:0.19 rgba(184, 160, 168, 255), stop:0.25 rgba(171, 186, 248, 255), stop:0.32 rgba(243, 248, 224, 255), stop:0.385 rgba(249, 162, 183, 255), stop:0.47 rgba(100, 115, 124, 255), stop:0.58 rgba(251, 205, 202, 255), stop:0.65 rgba(170, 128, 185, 255), stop:0.75 rgba(252, 222, 204, 255), stop:0.805 rgba(206, 122, 218, 255), stop:0.86 rgba(254, 223, 175, 255), stop:0.91 rgba(254, 236, 244, 255), stop:1 rgba(255, 191, 221, 255))");break;
    case 2048:
        backg.append("qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 red, stop:0.166 rgba(255, 255, 0, 255), stop:0.333 green, stop:0.5 rgba(0, 255, 255, 255), stop:0.666 blue, stop:0.833 purple, stop:1 red)");
        int answer=
                QMessageBox::question(this,"2048 found winner!","My congratulations!!!\nYou have been played for a long time I think.\nDo you want to exit or continue?","Continue","Exit");
        if(answer==1)QApplication::exit();
        break;
    }
    myNum[col][row]->setStyleSheet(backg+";font-size:30px;");
}

void table::create(){
    int add=2;
    if((qrand()%4)==0)add=4;
    bool complete=0;
    for(int r=0; r<4; r++){
        for(int c=0; c<4; c++){
            if(c==3 && r==3){
                QMessageBox::critical(this,"Big ERROR!!!","You have losed!                                 ");
                for(int i=0;i<30;i++)moveWidget(this,qrand()%800,qrand()%400,20);
                QApplication::exit(100);
                break;
            }
            int col,row; col=qrand()%4;row=qrand()%4;
            if(scores[col][row]==0){
                setScore(add,col,row);
                complete=1;
                break;
            }
        }
        if(complete)break;
    }
}

 table::~table()
{
    delete ui;
}
void table::up(int c, int r){
    if(r>0 && scores[c][r-1]==0){
        setScore(scores[c][r],c,r-1);
        setScore(0,c,r);
    }else if(r>0 && scores[c][r-1]==scores[c][r]){
        setScore(scores[c][r]*2,c,r-1);
        setScore(0,c,r);
    }
}
void table::down(int c, int r){
    if(r<3 && scores[c][r+1]==0){
        setScore(scores[c][r],c,r+1);
        setScore(0,c,r);
    }else if(r<3 && scores[c][r+1]==scores[c][r]){
        setScore(scores[c][r]*2,c,r+1);
        setScore(0,c,r);
    }
}
void table::left(int c, int r){
    if(c>0 && scores[c-1][r]==0){
        setScore(scores[c][r],c-1,r);
        setScore(0,c,r);
    }else if(c>0 && scores[c-1][r]==scores[c][r]){
        setScore(scores[c][r]*2,c-1,r);
        setScore(0,c,r);
    }
}
void table::right(int c, int r){
    if(c<3 && scores[c+1][r]==0){
        setScore(scores[c][r],c+1,r);
        setScore(0,c,r);
    }else if(c<3 && scores[c+1][r]==scores[c][r]){
        setScore(scores[c][r]*2,c+1,r);
        setScore(0,c,r);
    }
}

void table::on_Up_triggered()
{
    for(int how=0;how<5;how++)for(int c=0; c<4; c++)for(int r=0; r<4; r++){
        up(c,r);
    }
    create();
}

void table::on_Down_triggered()
{
    for(int how=0;how<5;how++)for(int c=3; c>=0; c--)for(int r=3; r>=0; r--){
        down(c,r);
    }
    create();
}

void table::on_Left_triggered()
{
    for(int how=0;how<5;how++)for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        left(c,r);
    }
    create();
}

void table::on_Right_triggered()
{
    for(int how=0;how<5;how++)for(int r=3; r>=0; r--)for(int c=3; c>=0; c--){
        right(c,r);
    }
    create();
}

void table::on_cheat_triggered()
{
    setScore(1024,0,0);
    setScore(512,0,1);
    setScore(256,0,2);
    setScore(256,0,3);
}
