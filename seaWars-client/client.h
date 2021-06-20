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
    int gamePin;
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
    void newMessage(QString);
};
#endif // CLIENT_H
