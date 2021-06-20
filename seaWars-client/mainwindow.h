#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <thread>
#include "client.h"
#include "Field.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    unsigned msg_count=0;
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
public slots:
    void addMessage(QString msg);
private slots:
    void onGameEnd();
    void on_act_server_triggered();
    void on_act_EndPlacing_triggered();
    void field2_clicked();
    void on_act_Shoot_triggered();
    void Shoot_recieved(int x, int y);
    void missed();
    void hitted();
    void on_msg_edit_returnPressed();
};

#endif // MAINWINDOW_H
