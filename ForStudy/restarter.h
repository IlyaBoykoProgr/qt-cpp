#ifndef RESTARTER_H
#define RESTARTER_H
#include <QObject>
#include <QProcess>
#include <QGuiApplication>

class Restarter : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void restart(){
        QProcess y;
        y.startDetached(QGuiApplication::applicationFilePath(),QGuiApplication::arguments());
        QGuiApplication::exit();
    }
};

#endif // RESTARTER_H
