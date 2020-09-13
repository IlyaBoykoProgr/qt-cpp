#include "mainfolder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFolder w;
    w.show();
    return a.exec();
}
