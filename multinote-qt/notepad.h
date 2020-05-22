#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTabWidget>
#include <QCloseEvent>
#include "ui_notepad.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow{
    Q_OBJECT
    void anim(){
        int h=height();
        for(int i=h;i<h*1.5;i+=2){resize(width(),i);move(x(),y()-1);}
        for(int i=h*1.5;i>=h;i-=2){resize(width(),i);move(x(),y()+1);repaint();}
    }
    void animErr(){
        int w=width();
        for(int i=w;i<w*1.5;i+=4){resize(i,height());move(x()-2,y());repaint();}
        for(int i=w*1.5;i>=w;i-=4){resize(i,height());move(x()+2,y());repaint();}
    }
public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();
    Ui::Notepad *ui;
    QTabWidget* files;

private slots:
    void on_act_New_triggered();
    void on_act_Save_triggered();
    void on_act_Open_triggered();
    void on_act_Remove_triggered();
    void on_act_NoSave_triggered();
    void on_act_About_triggered();
    void closeTab();
    void closeEvent(QCloseEvent* event);
    void on_act_NewWindow_triggered();
    void on_act_Rename_triggered();
    void on_act_Info_triggered();
    void on_act_Restart_triggered();
};
#endif // NOTEPAD_H
