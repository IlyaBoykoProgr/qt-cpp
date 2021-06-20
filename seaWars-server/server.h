#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QCoreApplication>
#include <iostream>

typedef struct player{
    QTcpSocket* sock=0;
    int pin;
} player;

class Server : public QTcpServer
{
    Q_OBJECT
    QList<player*> players;
    QList<int> available_pins;
    player* playerBySock(QTcpSocket*);
    player* pair(player*);
public:
    Server(QObject* parent=nullptr);
    ~Server();
private slots:
    void newPlayerConnecting();
    void playerWriting();
    void playerDisconnected();
};

#endif // SERVER_H
