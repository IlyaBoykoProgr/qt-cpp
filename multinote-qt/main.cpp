#include "notepad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    w.show();
    QObject::connect(w.ui->act_Quit,SIGNAL(triggered()),&a,SLOT(quit()));
    return a.exec();
}
