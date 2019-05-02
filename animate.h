#include <QWidget>
#include <QThread>
void moveWidget(QWidget* moving,int x,int y,long msTime){
    //Qt::WindowFlags flag= moving->windowFlags();
    //moving->setWindowFlags(Qt::Window);
    int repCount=msTime;
    if(repCount>x)repCount=x;
    if(repCount>y)repCount=y;
    double xChange=x - moving->x(); xChange/=repCount;
    double yChange=y - moving->y(); yChange/=repCount;
    while(repCount>=0){
        moving->move(moving->x()+xChange,moving->y()+yChange);
	 moving->update();
        QThread::msleep(1);
        repCount--;
    }
    //moving->setWindowFlags(flag);
    moving->move(x,y);
}

void sizeWidget(QWidget *sizing,int w,int h,long msTime){
   Qt::WindowFlags flag= sizing->windowFlags();
    sizing->setWindowFlags(Qt::Window);
    int repCount=msTime/5;
    if(repCount>w)repCount=w;
    if(repCount>h)repCount=h;
    double wChange=w - sizing->width(); wChange/=repCount;
    double hChange=h - sizing->height(); hChange/=repCount;
    while(repCount>=0){
	 sizing->resize(sizing->width()+wChange,sizing->height()+hChange);
	 sizing->update();
	 QThread::msleep(5);
        repCount--;
    }
   sizing->setWindowFlags(flag);
    sizing->resize(w,h);
}
