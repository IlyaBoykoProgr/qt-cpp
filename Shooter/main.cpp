#include "shooter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  shooter w(a.applicationFilePath());
  w.show();
  return a.exec();
}
