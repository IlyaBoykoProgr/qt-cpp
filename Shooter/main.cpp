#include "shooter.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
  int code=0;
  QApplication a(argc, argv);
  while(code!=123){
    srand(QTime::currentTime().msec());
    shooter w;
    w.show();
    code =a.exec();
  }
  return 0;
}
