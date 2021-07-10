#include "server.h"
#include <QCoreApplication>
int main(int argc,char** argv)
{
   srand(clock());
   QCoreApplication a(argc,argv);
   Server serv;
   if(serv.isListening()){
       qDebug()<<"Port   :"<<serv.serverPort();
       qDebug()<<"Address:"<<serv.serverAddress().toString();
   }
   return a.exec();
}
