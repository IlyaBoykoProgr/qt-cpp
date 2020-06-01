#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "client.h"
#include "Field.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum state{
        ST_PLACE, ST_ATTACK, ST_PROTECT
    };
    state State=ST_PLACE;
    Ui::MainWindow *ui;
    Field* field1;
    Field* field2;
    Client* socket=0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_act_NewGame_triggered();
    void on_act_EndPlacing_triggered();
    void field2_clicked();
    void on_act_Shoot_triggered();
    void Shoot_recieved(int x, int y);
    void missed();
    void hitted();
};

#endif // MAINWINDOW_H
