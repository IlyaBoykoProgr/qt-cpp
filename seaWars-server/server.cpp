#include "server.h"

Server::Server(QObject* parent):QTcpServer(parent)
{
    QString address="127.0.0.1";
    for(int i=QNetworkInterface::allAddresses().length()-1;i>-1;i--)
        if(QNetworkInterface::allAddresses()[i].toString().left(8)=="192.168.")
            address=QNetworkInterface::allAddresses()[i].toString();
    if(this->listen(QHostAddress(address),8080)){
        std::cout<<"Listening";
        if(address.isNull())std::cout<<"SERVER WORKS ONLY AT THIS MASHINE because no public adresses left";
    }
    else {
        std::cout<<"Don't listening.";
        QCoreApplication::quit();
    }
    connect(this,&QTcpServer::newConnection,this,&Server::newPlayerConnecting);
    setMaxPendingConnections(2);
}

void Server::newPlayerConnecting(){
    players.append(new player);
    players.last()->sock = nextPendingConnection();
    std::cout<<"Player    connected. Current players: "<<players.size()<<'\r';
    if(available_pins.isEmpty()){
        players.last()->pin = rand();
        available_pins.append(players.last()->pin);
        players.last()->sock->write("1 ");
        players.last()->sock->write(
            //ah yes, crossplatform
            QString::number(players.last()->pin).toStdString().c_str()
        );
    }else{
        players.last()->pin = available_pins.takeAt(0);

        players.last()->sock->write("2");
        pair(players.last())->sock->write("enemyfound");
    }
    connect(players.last()->sock,&QTcpSocket::disconnected,this,&Server::playerDisconnected);
    connect(players.last()->sock,&QTcpSocket::readyRead,this,&Server::playerWriting);
}

void Server::playerWriting(){
    //data sender
    player* p1 = playerBySock((QTcpSocket*)sender());
    //opponent
    player* p2 = pair(p1);
    if(p2==nullptr){
        p1->sock->write("noenemy");
        return;
    }
    QString data=p1->sock->readAll();
    if(data=="ready")
        p2->sock->write("enemyready");
    if(data.startsWith("shoot ")){
        QString parse=data.right(data.length()-6);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        p2->sock->write(("shooted "+QString::number(x)+" "+QString::number(y)).toStdString().c_str());
    }
    if(data.startsWith("msg "))
        p2->sock->write(data.toStdString().c_str());
    if(data=="miss" || data=="hit")
        p2->sock->write(data.toStdString().c_str());
}

void Server::playerDisconnected(){
    player* disconnected = playerBySock((QTcpSocket*)sender());
    if(disconnected==nullptr)return;
    disconnected->sock->close();
    players.removeOne(disconnected);
    delete disconnected;

    player* opponent = pair(disconnected);
    if(opponent==nullptr)return;
    opponent->sock->write("enemydis");
    opponent->sock->close();
    delete opponent;
    players.removeOne(opponent);

    std::cout<<"Player disconnected. Current players: "<<players.size()<<'\r';
}

Server::~Server(){
    std::cout<<"\nSERVER CLOSED";
}

player* Server::playerBySock(QTcpSocket *sock){
    for(player* i:players)
        if(i->sock == sock)
            return i;
    return nullptr;
}

player* Server::pair(player *p){
    for(player* i: players){
        if(i==p)continue;
        if(i->pin == p->pin)return i;
    }
    return nullptr;
}
