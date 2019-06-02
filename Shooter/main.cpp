#include "shooter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  shooter w;
  w.show();

  return a.exec();
}
