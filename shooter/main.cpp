#include "turrel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    turrel w;
    w.show();

    return a.exec();
}
