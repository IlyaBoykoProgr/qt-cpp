#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <math.h>
//comments have writen in Russian
///длина графика (по х)
#define WIDTH 100
///максимальная высота графика (по у)
#define HEIGHT 300
///точность, чем меньше, тем больше вероятность вылета системы)
#define TOCHNOST 0.05
///масштаб в 1:
#define SIZE 30

double f(double &x){
    return  sin(x*cos(x*x));//Тут пишите функцию для графика, return обязательно.
}

int main(int argc, char *argv[]){
 QApplication a(argc, argv);
 //MainWindow w;
 //w.show();
 QGraphicsScene scene;
 QGraphicsView view(&scene);
 view.centerOn(WIDTH/2, HEIGHT/2);
 double firstx=-WIDTH;
 for(double x=-WIDTH;x<WIDTH;x+=TOCHNOST){
   if(f(x)>HEIGHT||f(x)<-HEIGHT)continue;
   scene.addLine(firstx*SIZE,-f(firstx)*SIZE,x*SIZE,-f(x)*SIZE);
   firstx=x;
  }
 view.show();
 return a.exec();
}
