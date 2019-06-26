#include "shooter.h"
#include <QApplication>
#include <QTime>
#include <fstream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  srand(QTime::currentTime().msec());
  std::ifstream is("shooter-data",std::ios::nocreate);
  if(! is.is_open() ){
  is.close();
  std::ofstream data("shooter-data");
  data.close();
  }
  shooter w(a.applicationFilePath());
  w.show();
  return a.exec();
}
