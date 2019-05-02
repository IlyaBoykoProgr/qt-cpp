#include "table.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    QApplication a(argc, argv);
    table w;
    return a.exec();
}
