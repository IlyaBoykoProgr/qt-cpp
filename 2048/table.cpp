#include "table.h"
#include "ui_table.h"
#include <QThread>
#include <QScreen>

void moveWidget(QWidget* moving,int x,int y,long msTime,int repCount=700){
    float wait=msTime/repCount;
    if(repCount>x)repCount=x;
    if(repCount>y)repCount=y;
    double xChange=x - moving->x(); xChange/=repCount;
    double yChange=y - moving->y(); yChange/=repCount;
    while(repCount>=0){
        moving->move(moving->x()+xChange,moving->y()+yChange);
        QThread::msleep(wait);
        repCount--;
    }
    moving->move(x,y);
}

int scores[4][4];
QPushButton *myNum[4][4];
class num{
    int r, c;
public:
    num(int row,int col){
        r=row; c=col;
        setScore(0);
        if((qrand()%6)==0)setScore(2);
        else scores[r][c]=0;
    }
    void setScore(int score){
        scores[r][c]=score;
        if(score==0){
            myNum[r][c]->setStyleSheet("");
            myNum[r][c]->setText("");
            return;
        }
        myNum[r][c]->setText(QString::number(score));
        QString color=QString::number((2048-score)/409);
        myNum[r][c]->setStyleSheet("background:rgb(255,"+color+","+color+");");
    }
    void up(){
    }
    void down(){
    }
    void left(){
    }
    void right(){
    }
};
num* nums[4][4];

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    show();
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        myNum[r][c]= new QPushButton(this);
        myNum[r][c]->setFixedSize(90,90);
        myNum[r][c]->move(r*100,c*100);
        nums[r][c]= new num(r,c);
    }
    setFixedSize(400,400);
}

void table::paintEvent(QPaintEvent *e){
    QSize screen=QApplication::screens().at(0)->availableSize();
    moveWidget(this,screen.width()/2-100, screen.height()/2-100, 200);
}

void table::create(){
    int add=2;
    if((qrand()%6)==0)add=4;
    int row=qrand()%4,col=qrand()%4;
    while(scores[row][col]!=0){row=qrand()%4;col=qrand()%4;}
    nums[row][col]->setScore(add);
}

table::~table()
{
    delete ui;
}

void table::on_Up_triggered()
{
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        nums[r][c]->up();
    }
    create();
}

void table::on_Down_triggered()
{
    for(int r=3; r>=0; r--)for(int c=0; c<4; c++){
        nums[r][c]->down();
    }
    create();
}

void table::on_Left_triggered()
{
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        nums[r][c]->left();
    }
    create();
}

void table::on_Right_triggered()
{
    for(int r=0; r<4; r++)for(int c=3; c>=0; c--){
        nums[r][c]->right();
    }
    create();
}
