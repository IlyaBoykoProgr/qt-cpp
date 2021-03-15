#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QMainWindow>
#include "ui_infowindow.h"
#include <windows.h>

class InfoWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit InfoWindow(UINT_PTR hwnd);
    ~InfoWindow(){delete ui;delete where;}
private slots:
    void on_minimize_wnd_clicked();
    void on_maximize_wnd_clicked();
    void on_show_wnd_clicked();
private:
    QWidget* where;
    int timer;
    HWND wnd;
    Ui::InfoWindow *ui;
    void timerEvent(QTimerEvent* event);
    void closeEvent(QCloseEvent* event){Q_UNUSED(event);killTimer(timer);where->hide();}
};

#endif // INFOWINDOW_H
