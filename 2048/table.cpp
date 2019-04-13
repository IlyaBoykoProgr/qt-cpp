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
    QString color=QString::number(255.0-score/8);
    myNum[col][row]->setStyleSheet("\
        background:rgb("+color+","+color+","+color+");\
        font-size:30px;\
    ");
}

void table::create(){
    int add=2;
    if((qrand()%4)==0)add=4;
    int row=0,col=0;
    int gameOver=0;
    while(scores[row][col]!=0){
        for(col=col;col<4;col++){
            if(gameOver==15){
                QMessageBox::critical(this,"Big ERROR!!!","You have losed!                                 ");
                for(int i=0;i<30;i++)moveWidget(this,qrand()%800,qrand()%400,20);
                break;
            }
        }
        gameOver++;
        row++;
        col=0;
    }
    setScore(add,row,col);
    if(gameOver==15)QApplication::exit(100);
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
