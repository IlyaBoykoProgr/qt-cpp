#include "client.h"

Client::Client()
{
    isOpened=start();
    connect(this,SIGNAL(readyRead()),this,SLOT(serverSending()));
    connect(this,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
}

bool Client::start(){
    QString address;
    for(int i=100;i<150;i++){
        address="192.168.0."+QString::number(i);
        this->connectToHost(address,8080);
        if(waitForConnected(200))return 1;
    }
    QString newAddr=QInputDialog::getText(nullptr,"Неудача","Не удалось подключится к серверу SeaWars.\n"
                              "Возможно, он не запущен или вы не имеете подключения к интернету.\n"
                              "Ошибка: "+errorString()+". IP: "+address+"\n"
                              "Если вы хотите подключится к другому адресу, введите его в поле ниже:",
                              QLineEdit::Normal);
    if(newAddr==address)return 0;
    else this->connectToHost(address=newAddr,8080);
    return 1;
}

void Client::serverSending(){
    QString data=this->readAll();
    if(data.startsWith("1 ")){
        index=1;
        emit newMessage("Вы подключились!\nЖдем соперника...");
        gamePin = data.sliced(data.indexOf(' ')).toUInt();
    }
    if(data=="2"){
        index=2;
        emit newMessage("Вы нашли игру.\nПартия началсь!");
    }
    if(data.startsWith("shooted ")){
        QString parse=data.right(data.length()-8);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.sliced(parse.indexOf(' ')).toInt();
        emit youWereShooted(x,y);
    }
    if(data=="hit")emit youHitted();
    if(data=="miss")emit youMissed();
    if(data.startsWith("msg ")){
        if(data.length()==4)return;
        emit newMessage("Сообщение от противника:\n\""+data.remove(0,4)+"\"");
    }
    if(data=="enemyfound")emit newMessage("Противник найден! Игра начинается");
    if(data=="enemyready")emit newMessage("Противник расставил\nкорабли");
    if(data=="noenemy")emit newMessage("Оппонент еще не подключился к серверу!");
    if(data=="enemydis"){
        emit newMessage("Противник отключился.\nПартия окончена");
        this->close();
        isOpened= false;
    }
}

Client::~Client(){
    this->disconnectFromHost();
}

void Client::onDisconnect(){
    isOpened=false;
    emit newMessage("Вы отключились от сервера!");
}

bool Client::isOpen(){
    return isOpened;
}
