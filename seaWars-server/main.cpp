#include "server.h"
#include <QCoreApplication>
int main(int argc,char** argv)
{
   QCoreApplication a(argc,argv);
   Server serv;
   qDebug()<<"\a\a";
   qDebug()<<"Port   :"<<serv.serverPort();
   qDebug()<<"Address:"<<serv.serverAddress().toString();
   return a.exec();
}
