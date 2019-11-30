#ifndef UNIVERSAL_H
#define UNIVERSAL_H

#include <QMainWindow>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QMessageBox>

class Universal : public QMainWindow
{
    Q_OBJECT
    QPushButton*** cells;
    bool** state;
    int COUNT, size;
    bool isPlaying=0;
protected:
    void timerEvent(QTimerEvent *event);
    short neighbors(bool **cells, int x, int y);
    void mousePressEvent(QMouseEvent *event);
public:
    Universal(int count, int size);
    ~Universal();
};

#endif // UNIVERSAL_H
