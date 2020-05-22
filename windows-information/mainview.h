#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "ui_mainview.h"
#include "infowindow.h"
#include <QMainWindow>
#include <QLabel>

class MainView : public QMainWindow
{
    Q_OBJECT
    Ui::MainView* ui= new Ui::MainView;
public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView(){delete ui;}
private:
    void paintEvent(QPaintEvent* event);
private slots:
    void on_showVisible_stateChanged(int);
    void on_tableWidget_cellDoubleClicked(int row,int col);
    void on_refresh_clicked();
};

#endif // MAINVIEW_H
