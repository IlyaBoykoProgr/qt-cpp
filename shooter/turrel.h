#ifndef TURREL_H
#define TURREL_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QGraphicsScene>

namespace Ui {
class turrel;
}

class turrel : public QMainWindow
{
    Q_OBJECT

public:
    explicit turrel(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* ev);
    ~turrel();

private:
    Ui::turrel *ui;
    QGraphicsScene* front= new QGraphicsScene();
    short x=20;
};

#endif // TURREL_H
