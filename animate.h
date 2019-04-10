#include <QWidget>
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