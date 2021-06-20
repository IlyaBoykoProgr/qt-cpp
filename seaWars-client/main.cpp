#include "client.h"
#include "mainwindow.h"
#include <QApplication>

MainWindow* w=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    do{
        if(w!=0)delete w;
        w = new MainWindow;
        w->show();
    }while(a.exec()!=0);
    return 0;
}
