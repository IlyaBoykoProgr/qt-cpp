#ifndef XO_H
#define XO_H
#include <QPushButton>
#include <QStatusBar>
#include <QObject>

class XO : public QObject
{
    Q_OBJECT
public:
    explicit XO(QObject *parent = 0);
    QPushButton *myBut;
    QStatusBar *myStatus;
    void start();
    void setX();
    void setO();
    void setBut(QPushButton *parent, QStatusBar *bar);
signals:

public slots:
    void clicked();
};

#endif // XO_H
