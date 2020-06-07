#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QCoreApplication>
#include <QDebug>

class Server : public QTcpServer
{
    Q_OBJECT
    QTcpSocket *sock1=0,*sock2=0;
    bool boats1[10][10], boats2[10][10];
    void parseTable(QString boats,bool array[10][10]);
public:
    Server(QObject* parent=nullptr);
    ~Server();
private slots:
    void newPlayerConnecting();
    void player1Writing();
    void player2Writing();
    void player1Disconnected();
    void player2Disconnected();
};

#endif // SERVER_H
