#ifndef PAGE_H
#define PAGE_H
#include <QTabWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QMessageBox>
#include "notepad.h"
using namespace std;

class Page : public QWidget{
    QTextEdit edit;
    QTabWidget* tabs;
 public:
    int index;
    QString file;
    Page(QTabWidget* parent=nullptr):QWidget(parent){
        tabs=parent;
        tabs->addTab(this,"Новый документ");
        index=tabs->indexOf(this);
        setLayout(new QVBoxLayout(this));
        layout()->addWidget(&edit);
        edit.show();
    }
    bool save(){
        if(file.isEmpty()){
            file= QFileDialog::getSaveFileUrl(this,"Выберите место для сохранения").toString().right(8);
        }
        if(file.isEmpty())return false;
        QFile f(file);
        if(!f.open(QIODevice::Truncate|QIODevice::ReadWrite))
            return false;
        f.write(edit.toPlainText().toLocal8Bit());
        tabs->setTabText(index,f.fileName());
        f.close();
        return true;
    }
    void open(QUrl adress){
        file=adress.toString().right(8);
        QFile f(file);
        f.open(QIODevice::ReadWrite|QIODevice::Text);
        tabs->setTabText(index,f.fileName());
        edit.setText(QString(f.readAll()));
        f.close();
    }
    ~Page(){
        tabs->removeTab(index);
    }
};

#endif // PAGE_H
