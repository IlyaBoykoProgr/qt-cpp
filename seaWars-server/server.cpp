#include "server.h"

Server::Server(QObject* parent):QTcpServer(parent)
{
    if(this->listen(QNetworkInterface::allAddresses().at(0),8080))
        qDebug()<<"Listening";
    else {
        qDebug()<<"Don't listening. Error: "+errorString();
        QCoreApplication::quit();
    }
    connect(this,SIGNAL(newConnection()),(Server*)this,SLOT(newPlayerConnecting()));
    setMaxPendingConnections(2);
}

void Server::newPlayerConnecting(){
    if(!sock1){
        sock1= nextPendingConnection();
        sock1->write("1");
        qDebug()<<"Player 1 connected";
        connect(sock1,SIGNAL(readyRead()),this,SLOT(player1Writing()));
        connect(sock1,SIGNAL(disconnected()),this,SLOT(player1Disconnected()));
    }
    else if(!sock2){
        sock2= nextPendingConnection();
        sock2->write("2");
        qDebug()<<"Player 2 connected";
        connect(sock2,SIGNAL(readyRead()),this,SLOT(player2Writing()));
        connect(sock2,SIGNAL(disconnected()),this,SLOT(player2Disconnected()));
    }
    else{
        nextPendingConnection()->write("3");
        qDebug()<<"3rd player tryed to connect";
    }
}

void Server::player1Writing(){
    QString data=sock1->readAll();
    qDebug()<<"1st player sent "<<data;
    if(data.startsWith("ready ")){
        qDebug()<<"1st player is ready";
        parseTable(data.right(100),boats1);
        qDebug()<<"1st player's boats recieved";
    }
    if(data.startsWith("shoot ")){
        QString parse=data.right(data.length()-6);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        sock2->write(("shooted "+QString::number(x)+" "+QString::number(y)).toStdString().c_str());
        qDebug()<<"Player 1 shoots at "<<x<<" "<<y;
    }
    if(data=="miss")sock2->write("miss");
    if(data=="hit"){sock2->write("hit");hits2++;
        if(hits2==20){sock2->write("win");sock1->write("lose");}
    }
}
void Server::player2Writing(){
    QString data=sock2->readAll();
    qDebug()<<"2nd player sent "<<data;
    if(data.startsWith("ready ")){
        qDebug()<<"2nd player is ready";
        parseTable(data.right(100),boats2);
        qDebug()<<"2nd player's boats recieved";
    }
    if(data.startsWith("shoot ")){
        QString parse=data.right(data.length()-6);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        sock1->write(("shooted "+QString::number(x)+" "+QString::number(y)).toStdString().c_str());
        qDebug()<<"Player 2 shoots at "<<x<<" "<<y;
    }
    if(data=="miss")sock1->write("miss");
    if(data=="hit"){sock1->write("hit");hits1++;
        if(hits1==20){sock1->write("win");sock2->write("lose");}
    }
}

void Server::parseTable(QString boats,bool array[10][10]){
    for(int x=0;x<10;x++)for(int y=0;y<10;y++){
        array[x][y]=QString(boats.at((x+1)*(y+1)-1)).toInt();
    }
}
void Server::player1Disconnected(){
    qDebug()<<"1st player has disconnected";
    sock1=0;
}
void Server::player2Disconnected(){
    qDebug()<<"2nd player has disconnected";
    sock2=0;
}

Server::~Server(){
    qDebug()<<"\nSERVER CLOSED\a";
}
