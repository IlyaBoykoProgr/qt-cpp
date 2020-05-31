#include "shooter.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  srand(QTime::currentTime().msec());
  shooter w;
  w.startTimer(1500);
  w.show();
  return a.exec();
}
