#include "wind.h"
#include "xo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wind w;
    w.show();
    return a.exec();
}
