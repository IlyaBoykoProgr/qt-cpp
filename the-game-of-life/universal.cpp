#include "universal.h"

#define everyCell for(int x=0;x<COUNT;x++)for(int y=0;y<COUNT;y++)
#define CELL (size/COUNT)
#define live setChecked(true)
#define isLive isChecked()
#define die setChecked(false)

Universal::Universal(int count,int size)
{
    this->size=size;  COUNT=count;  resize(size,size);
    cells= new QPushButton**[COUNT];//Creating cells
    for(int i=0;i<COUNT;i++)cells[i]=new QPushButton*[COUNT];
    everyCell{
        cells[x][y]=new QPushButton(this);
        cells[x][y]->setGeometry(x*CELL,y*CELL,CELL,CELL);
        cells[x][y]->setCheckable(true);
        cells[x][y]->setFlat(true);
        cells[x][y]->show();
    }
    state= new bool*[COUNT];//Creating states of cells
    for(int i=0;i<COUNT;i++)state[i]=new bool[COUNT];
    startTimer(20);
    QMessageBox::information(this,"Info:","Press right mouse key \nto pause/play the game.");
}

void Universal::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    if(!isPlaying)return;
    everyCell{state[x][y]=cells[x][y]->isLive;}
    everyCell{
        short n = neighbors(state,x,y);
        if(n==3||(n==2&&cells[x][y]->isLive))cells[x][y]->live;
        else cells[x][y]->die;
    }
}

short Universal::neighbors(bool** cells,int x, int y){
    short answer=0;
    if(x!=0){
        if(y!=0)answer+=cells[x-1][y-1];
        answer+=cells[x-1][y];
        if(y!=(COUNT-1))answer+=cells[x-1][y+1];
    }
    if(y!=0){
        answer+=cells[x][y-1];
        if(x!=(COUNT-1))answer+=cells[x+1][y-1];
    }
    if(x!=(COUNT-1)){
        answer+=cells[x+1][y];
        if(y!=(COUNT-1))answer+=cells[x+1][y+1];
    }
    if(y!=(COUNT-1))
        answer+=cells[x][y+1];
    return answer;
}

void Universal::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton)isPlaying=!isPlaying;
}

Universal::~Universal()
{

}
