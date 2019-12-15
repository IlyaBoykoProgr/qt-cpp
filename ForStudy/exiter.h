#ifndef EXITER_H
#define EXITER_H
#include <QCoreApplication>

class exiter :public QObject{
    Q_OBJECT
public slots:
    void exit(int code){
        QCoreApplication::exit(code);
    }
};

#endif // EXITER_H
