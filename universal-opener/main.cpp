#include "opener.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    opener w;
    w.show();

    return a.exec();
}
