#include "shooter.h"
#include "database.h"
#include <QApplication>
#include <QFileDialog>
#include <QTime>
#include <fstream>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  srand(QTime::currentTime().msec());
  std::ifstream is("path");
  if(! is.is_open() ){
  is.close();
  QString path=QFileDialog::getExistingDirectory(nullptr,"Where is the data?",
             #ifdef Q_OS_UNIX
                   "/home"
             #elif Q_OS_WIN32
                   "C:\\"
             #endif
             );
  std::ofstream savePath("path");
  savePath<<path.toStdString();
  savePath.close();
  savePath.open(bin::path(),std::ios_base::in);
  if(!savePath.is_open())bin::set(0,0);
  }
  shooter w(&a);
  w.show();
  return a.exec();
}
