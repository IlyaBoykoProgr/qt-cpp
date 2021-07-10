#include "server.h"

Server::Server(QObject* parent):QTcpServer(parent)
{
    QString address="127.0.0.1";
    qDebug()<<QNetworkInterface::allAddresses();
    for(int i=QNetworkInterface::allAddresses().length()-1;i>-1;i--)
        if(QNetworkInterface::allAddresses()[i].toString().left(8)=="192.168.")
            address=QNetworkInterface::allAddresses()[i].toString();
    if(this->listen(QHostAddress(address),7676)){
        std::cout<<"Listening\n";
        if(address.isNull())std::cout<<"\nSERVER WORKS ONLY AT THIS MASHINE because no public adresses left\n";
    }
    else {
        std::cout<<"\nnot listening.\n";
        deleteLater();
    }
    connect(this,&QTcpServer::newConnection,this,&Server::newPlayerConnecting);
    setMaxPendingConnections(2);
}

void Server::newPlayerConnecting(){
    //removing ghosts
        while(players.removeOne(nullptr));
        for(player* i: players)
            if(i->sock==nullptr&&!i->sock->isOpen())
                players.removeOne(i);
        players.shrink_to_fit();
    //removed ghosts
    players.append(new player);
    players.last()->sock = nextPendingConnection();
    if(available_pins.isEmpty()){
        players.last()->pin = rand();
        available_pins.append(players.last()->pin);
        players.last()->sock->write("1");
    }else{
        players.last()->pin = available_pins.takeAt(0);
        players.last()->turn = true;
        players.last()->sock->write("2");
        if(pair(players.last())==nullptr){
            players.last()->sock->write("enemydis");
            players.last()->sock->close();
            return;
        }
        pair(players.last())->sock->write("enemyfound");
    }
    connect(players.last()->sock,&QTcpSocket::disconnected,this,&Server::playerDisconnected);
    connect(players.last()->sock,&QTcpSocket::readyRead,this,&Server::playerWriting);
}

void Server::playerWriting(){
    //data sender
    player* p1 = playerBySock((QTcpSocket*)sender());
    if(p1==nullptr)return; //just in case
    player* p2 = pair(p1);
    QString data=p1->sock->readAll();
    if(data.startsWith("enemyready")){
        bool valid = fieldParser::isValid(data.replace("enemyready","").toStdString().c_str());
        p1->sock->write(valid?"fieldaccept":"fieldwrong");
        if(p2!=nullptr){
            p2->sock->write("enemyready");
            return;
        }
    }
    //opponent
    if(p2==nullptr){
        p1->sock->write("noenemy");
        return;
    }
    if(data.startsWith("shoot ")){
        if(!p1->turn)return;
        p2->sock->write(data.replace("shoot","shooted").toStdString().c_str());
    }
    if(data=="miss"||data=="hit"){
        p1->turn = data=="hit";
        p2->turn = !p1->turn;
    }
    if(data.startsWith("msg "))
        p2->sock->write(data.toStdString().c_str());
}

void Server::playerDisconnected(){
    player* disconnected = playerBySock((QTcpSocket*)sender());
    if(disconnected==nullptr){
        disconnected->sock->close();
        players.removeOne(disconnected);
        player* opponent = pair(disconnected);
        delete disconnected;

        if(opponent!=nullptr){
            opponent->sock->write("enemydis");
            opponent->sock->close();
            delete opponent;
            players.removeOne(opponent);
        }
    }
    players.shrink_to_fit();
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
