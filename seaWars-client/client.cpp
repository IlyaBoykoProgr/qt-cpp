#include "client.h"

Client::Client()
{
    isOpened=start();
    connect(this,SIGNAL(readyRead()),this,SLOT(serverSending()));
    connect(this,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
}

bool Client::start(){
    this->connectToHost(
                QNetworkInterface::allAddresses()[0].toString(),8080);
    if(!waitForConnected()){
        QMessageBox::critical(nullptr,"Неудача","Не удалось подключится к серверу SeaWars.\n"
                              "Возможно, он не запущен или вы не имеете подключения к интернету.\n"
                              "Ошибка: "+errorString());
        return 0;
    }

    return 1;
}

void Client::serverSending(){
    QString data=this->readAll();
    if(data=="1")index=1;
    if(data=="2")index=2;
    if(data=="1"||data=="2"){
        QMessageBox::information(nullptr,"Удача","Вы подключились как 'игрок "+QString::number(index)+"'");
    }
    if(data=="3"){
        QMessageBox::critical(nullptr,"Неудача","Не удалось подключится к серверу SeaWars.\n"
                                                "Причина: двое игроков уже играют между собой");
    }
    if(data.startsWith("shooted ")){
        QString parse=data.right(data.length()-8);
        int x=parse.left(parse.indexOf(' ')).toInt();
        int y=parse.right(parse.length()-parse.indexOf(' ')-1).toInt();
        emit youWereShooted(x,y);
    }
    if(data=="hit"){emit youHitted();QMessageBox::information(nullptr,"Успех!","Вы попали!");}
    if(data=="miss"){emit youMissed();QMessageBox::information(nullptr,"Неудача","Вы не попали.");}
    if(data=="hitwin"){QMessageBox::information(nullptr,"Вы победили!","Победааа!!!!\nКорабли противника уничтожены!");}
    if(data=="lose"){QMessageBox::information(nullptr,"Вы проиграли","Противник уничтожил ваши корабли"
                                   "\nВы проиграли.\nНичего, еще выиграете!");}
    if(data=="hitwin"||data=="lose"){
        QProcess::startDetached(QApplication::applicationFilePath());
        QApplication::quit();
    }
}

Client::~Client()
{
    this->write("disconnected");
    this->disconnectFromHost();
    this->waitForDisconnected();
}

void Client::onDisconnect(){
    isOpened=false;
    QMessageBox::information(nullptr,"Важная информация","Вы отключились от сервера!Попытка переподключения...");
}

bool Client::isOpen(){
    return isOpened;
}
