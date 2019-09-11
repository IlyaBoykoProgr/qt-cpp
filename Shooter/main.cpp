#include "shooter.h"
#include "database.h"
#include <QApplication>
#include <QTime>
#include <fstream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  srand(QTime::currentTime().msec());
  std::ifstream is("shooter-data");
  if(! is.is_open() ){
  is.close();
  bin::set(0,0,false);
  }
  shooter w(&a);
  w.show();
  return a.exec();
}
