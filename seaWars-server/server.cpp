#include "server.h"
#include <iostream>

Server::Server(QObject* parent):QTcpServer(parent)
{
    QString address="127.0.0.1";
    foreach (auto i, QNetworkInterface::allAddresses()) {
       qDebug()<<i.toString();
    }
    for(int i=QNetworkInterface::allAddresses().length()-1;i>-1;i--)
        if(QNetworkInterface::allAddresses()[i].toString().left(8)=="192.168.")
            address=QNetworkInterface::allAddresses()[i].toString();
    if(this->listen(QHostAddress(address),8080)){
        qDebug()<<"Listening";
        if(address.isNull())qDebug()<<"SERVER WORKS ONLY AT THIS MASHINE because no public adresses left";
    }
    else {
        qDebug()<<"\a\a\a\aDon't listening. Error: "+errorString();
        QCoreApplication::quit();
    }
    connect(this,SIGNAL(newConnection()),(Server*)this,SLOT(newPlayerConnecting()));
    setMaxPendingConnections(2);
}

void Server::newPlayerConnecting(){
    std::cout<<"\a\a";
    if(sock1==0){
        sock1= nextPendingConnection();
        sock1->write("1");
        qDebug()<<"Player 1 connected";
        connect(sock1,SIGNAL(readyRead()),this,SLOT(player1Writing()));
        connect(sock1,SIGNAL(disconnected()),this,SLOT(player1Disconnected()));
    }
    else if(sock2==0){
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
    if(data.startsWith("ready ")){
        qDebug()<<"1st player is ready";
        parseTable(data.right(100),boats1);
        qDebug()<<"1st player's boats recieved";
        if(sock2!=0)sock2->write("enemyready");
        else sock1->write("noenemy");
    }
    if(data.startsWith("shoot ")){
        if(sock2==0){sock1->write("noenemy");return;}
        QString parse=data.right(data.length()-6);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        sock2->write(("shooted "+QString::number(x)+" "+QString::number(y)).toStdString().c_str());
        qDebug()<<"Player 1 shoots at "<<x<<" "<<y;
    }
    if(data.startsWith("msg ")){
        if(sock2!=0)sock2->write(data.toStdString().c_str());
        else sock1->write("noenemy");
    }
    if(data=="miss")sock2->write("miss");
    if(data=="hit")sock2->write("hit");
}
void Server::player2Writing(){
    QString data=sock2->readAll();
    if(data.startsWith("ready ")){
        if(data.length()!=106)return;
        qDebug()<<"2nd player is ready";
        parseTable(data.right(100),boats2);
        qDebug()<<"2nd player's boats recieved";
        if(sock1!=0)sock1->write("enemyready");
        else sock2->write("noenemy");
    }
    if(data.startsWith("shoot ")){
        if(sock1==0){sock2->write("noenemy");return;}
        QString parse=data.right(data.length()-6);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        sock1->write(("shooted "+QString::number(x)+" "+QString::number(y)).toStdString().c_str());
        qDebug()<<"Player 2 shoots at "<<x<<" "<<y;
    }
    if(data.startsWith("msg ")){
        if(sock1!=0)sock1->write(data.toStdString().c_str());
        else sock2->write("noenemy");
    }
    if(data=="miss")sock1->write("miss");
    if(data=="hit")sock1->write("hit");
}

void Server::parseTable(QString boats,bool array[10][10]){
    for(int x=0;x<10;x++)for(int y=0;y<10;y++){
        array[x][y]=QString(boats.at((x+1)*(y+1)-1)).toInt();
    }
    for(int i=0;i<10;i++){
        for(int t=0;t<100;t+=10)std::cout<<boats[i+t].toLatin1();
        std::cout<<'\n';
    }
    std::cout<<'\a';
}
void Server::player1Disconnected(){
    qDebug()<<"1st player has disconnected";
    std::cout<<'\a';
    sock1=0;
}
void Server::player2Disconnected(){
    qDebug()<<"2nd player has disconnected";
    std::cout<<'\a';
    sock2=0;
}

Server::~Server(){
    std::cout<<"\a\a\a\nSERVER CLOSED";
}