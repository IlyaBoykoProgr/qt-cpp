#include "table.h"
#include "../animate.h"
#include <QDebug>

table::table(QWidget *parent) :
    QMainWindow(parent)
{
    rows= QInputDialog::getInt(this,"Size of the table:","Write size of the table",4,2,30);
    if(rows<6)coff=0.5;
    else if(rows<=10)coff=1;
    else if(rows<=15)coff=2;
    else if(rows<=30)coff=4;
    setStyleSheet("QPushButton{border:"+QString::number(5/coff)+"px solid #CF9E52;font-size:"+QString::number(30/coff)+"px;}");
    setFixedSize(rows*70/coff,rows*70/coff);
    scores= new short int*[rows];
    for(int i=0; i<rows; i++)scores[i]= new short int[rows];
    myNum= new QPushButton**[rows];
    for(int i=0; i<rows; i++)myNum[i]= new QPushButton*[rows];
    for(int c=0; c<rows; c++)for(int r=0; r<rows; r++){
        myNum[c][r]=new QPushButton(this);
        myNum[c][r]->resize(70/coff,70/coff);
        myNum[c][r]->move(c*70/coff,r*70/coff);
        setScore(0,c,r);
        myNum[c][r]->repaint();
    }
    create();
    create();
    move(200,50);
    show();
    setFocus(Qt::FocusReason::ActiveWindowFocusReason);
}

void table::keyPressEvent(QKeyEvent* ev){
    switch(ev->key()){
    case Qt::Key_W:
    case Qt::Key_Up:on_Up_triggered(); break;
    case Qt::Key_S:
    case Qt::Key_Down:on_Down_triggered(); break;
    case Qt::Key_A:
    case Qt::Key_Left:on_Left_triggered(); break;
    case Qt::Key_D:
    case Qt::Key_Right:on_Right_triggered(); break;
    }
}

void table::focusOutEvent(QFocusEvent *ev){
    Q_UNUSED(ev);
    setFocus(Qt::FocusReason::ActiveWindowFocusReason);
}

void table::setScore(int score, int col, int row){
    scores[col][row]=score;
    switch(score){
        case 0: myNum[col][row]->setStyleSheet("background:#EFBE72;");break;
        case 2: myNum[col][row]->setStyleSheet("background:red;background-image:url(:/gems/gem3.png);");break;
        case 4: myNum[col][row]->setStyleSheet("background:orange;background-image:url(:/gems/gem7.png);");break;
        case 8: myNum[col][row]->setStyleSheet("background:yellow;background-image:url(:/gems/gem4.png);");break;
        case 16: myNum[col][row]->setStyleSheet("background:lime;background-image:url(:/gems/gem2.png);");break;
        case 32: myNum[col][row]->setStyleSheet("background:green;background-image:url(:/gems/gem2.png);");break;
        case 64: myNum[col][row]->setStyleSheet("background:aqua;background-image:url(:/gems/gem6.png);");break;
        case 128: myNum[col][row]->setStyleSheet("background:blue;background-image:url(:/gems/gem1.png);");break;
        case 256: myNum[col][row]->setStyleSheet("background:purple;background-image:url(:/gems/gem5.png);");break;
        case 512: myNum[col][row]->setStyleSheet("background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 blue, stop:1 purple);");break;
        case 1024: myNum[col][row]->setStyleSheet("background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 green, stop:0.5 blue, stop:1 purple);");break;
        case 2048: myNum[col][row]->setStyleSheet("background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:0.5 yellow, stop:1 green);");break;
        case 4096:myNum[col][row]->setStyleSheet("background:qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 red, stop:0.2 yellow, stop:0.4 green, stop:0.6 lightblue, stop:0.8 blue, stop:1 purple);");break;
    }
    if(score==0){
        myNum[col][row]->setText(" ");
        return;
    }
    myNum[col][row]->setText(QString::number(score));
    myNum[col][row]->repaint();
    if(score==2048&&!is2048created){
        QString style= myNum[col][row]->styleSheet();
        is2048created=true;
        setStyleSheet("QPushButton{border:"+QString::number(5/coff)+"px solid "+style.right(style.length()-11)+";font-size:"+QString::number(20/coff)+"px;}");
        int answer=
                QMessageBox::question(this,"2048: winner!","My congratulations!!!\nYou have just complete game.\nDo you want to exit or continue?","Continue","Exit");
        if(answer==1)QApplication::exit();
    }
    if(score==4096&&!is4096created){
        QString style= myNum[col][row]->styleSheet();
        is4096created=true;
        setStyleSheet("QPushButton{border:"+QString::number(5/coff)+"px solid "+style.right(style.length()-11)+";font-size:"+QString::number(20/coff)+"px;}");
        QMessageBox::critical(this,"OH MY GOD!!!","You're unstopppable, aren't you?\nHow did you make this?\nImpossible...");
    }
    if(score==8192){
        for(int i=0;i<40;i++){show();QThread::msleep(10);hide();}
        QMessageBox::critical(this,"stop doing this!","8192 is the largest number!");
        QApplication::exit(-1);
    }

    if(coff!=4)QThread::msleep(16/coff);
}

void table::create(){
    int add=2;
    if((qrand()%10)==0)add=4;
    bool complete=0;
    for(int r=0; r<rows; r++){
        for(int c=0; c<rows; c++){
            if(c==rows-1 && r==rows-1){
                if(QMessageBox::critical(this,"Big ERROR!!!","You have losed!",
                                      QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)break;
                for(int i=0;i<30;i++)moveWidget(this,qrand()%800,qrand()%400,20);
                QApplication::exit();
                break;
            }
            int col,row; col=qrand()%rows;row=qrand()%rows;
            if(scores[col][row]==0){
                setScore(add,col,row);
                complete=1;
                break;
            }
        }
        if(complete)break;
    }
}

void table::up(int c, int r){
    if(r>0 && scores[c][r-1]==0){
        setScore(scores[c][r],c,r-1);
        setScore(0,c,r);
    }else if(r>0 && scores[c][r-1]==scores[c][r]){
        setScore(scores[c][r]*2,c,r-1);
        setScore(0,c,r);
        for(short i=2;i<=(scores[c][r]*2);i+=i){
            setScore(i,c,r-1);
            repaint();
        }
    }
}
void table::down(int c, int r){
    if(r<rows-1 && scores[c][r+1]==0){
        setScore(scores[c][r],c,r+1);
        setScore(0,c,r);
    }else if(r<rows-1 && scores[c][r+1]==scores[c][r]){
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
    if(c<rows-1 && scores[c+1][r]==0){
        setScore(scores[c][r],c+1,r);
        setScore(0,c,r);
    }else if(c<rows-1 && scores[c+1][r]==scores[c][r]){
        setScore(scores[c][r]*2,c+1,r);
        setScore(0,c,r);
    }
}

void table::on_Up_triggered()
{
    for(int how=0;how<rows;how++)for(int c=0; c<rows; c++){
        for(int r=0; r<rows; r++)up(c,r);
    }
    create();
}

void table::on_Down_triggered()
{
    for(int how=0;how<rows;how++)for(int c=rows-1; c>=0; c--){
        for(int r=rows-1; r>=0; r--)down(c,r);
    }
    create();
}

void table::on_Left_triggered()
{
    for(int how=0;how<rows;how++)for(int r=0; r<rows; r++){
        for(int c=0; c<rows; c++)left(c,r);
    }
    create();
}
void table::on_Right_triggered()
{
    for(int how=0;how<rows;how++)for(int r=rows-1; r>=0; r--){
        for(int c=rows-1; c>=0; c--)right(c,r);
    }
    create();
}
