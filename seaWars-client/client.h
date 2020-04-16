#ifndef CLIENT_H
#define CLIENT_H
#include <QProcess>
#include <QApplication>
#include <QTcpSocket>
#include <QMessageBox>
#include <QInputDialog>
#include <QNetworkInterface>

class Client : public QTcpSocket
{
    Q_OBJECT
    bool isOpened;
public:
    int index;
    Client();
    ~Client();
    bool start();
    bool isOpen();
public slots:
    void onDisconnect();
    void serverSending();
signals:
    void youWereShooted(int x, int y);
    void youHitted();
    void youMissed();
};
#endif // CLIENT_H
