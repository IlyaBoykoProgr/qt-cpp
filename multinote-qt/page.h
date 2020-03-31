#ifndef PAGE_H
#define PAGE_H
#include <QThread>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include "notepad.h"
using namespace std;

class Page : public QWidget{
    QTextEdit edit;
    QTabWidget* tabs;
 public:
    int index;
    QString adress,filename,dir,type;
    Page(QTabWidget* parent=nullptr):QWidget(parent){
        tabs=parent;
        tabs->addTab(this,"Новый документ");
        index=tabs->indexOf(this);
        setLayout(new QVBoxLayout(this));
        layout()->addWidget(&edit);
        edit.show();
    }
    bool save(){
        if(edit.toPlainText().contains("пасхалка")){
            QWidget* ten[10];
            for (int i=0;i<10;i++){
                ten[i]= new QWidget;
                ten[i]->setGeometry(i*100,i*80,400,100);
                ten[i]->setWindowTitle("ПАСХАЛОЧКА");
                ten[i]->show();
                QThread::msleep(200);
            }QThread::sleep(1);
            for(int i=0;i<10;i++)delete ten[i];
        }
        if(adress.isEmpty()){
            adress= QFileDialog::getSaveFileUrl(this,"Выберите место для сохранения").toString().right(8);
        }
        if(adress.isEmpty())return false;
        QFile f(adress);
        if(!f.open(QIODevice::Truncate|QIODevice::ReadWrite))
            return false;
        f.write(edit.toPlainText().toLocal8Bit());
        tabs->setTabText(index,filename);
        f.close();
        return true;
    }
    void open(QUrl NewAdress){
        if(NewAdress.isEmpty())return;
        adress=NewAdress.toString().replace("file:///","");
        filename= NewAdress.fileName();
        dir=adress;dir.replace(filename,"");
        type=filename.right(filename.length()-(filename.lastIndexOf('.')+1));
        tabs->setTabText(index,filename);

        QFile qf(adress);
        qf.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(&qf);
        in.setAutoDetectUnicode(true);
        if(!(qf.isOpen()&&qf.isReadable())){
            QMessageBox::critical(this,"Ошибка","Ошибка чтения файла");
            qf.close();
            tabs->setTabEnabled(index,false);
            return;
        }
        edit.setText(in.readAll());
        qf.close();
    }
    bool rename(){
        QFile qf(adress);
        qf.open(QIODevice::ReadWrite);
        QString newName=QInputDialog::getText(this,"Переименование","Введите новое имя файла\n"
                         "Старое: "+filename,QLineEdit::Normal,filename);
        bool succ= qf.rename(newName);
        QUrl url=QUrl("file:///"+dir+'/'+newName);
        qf.close();
        open(url);
        return succ;
    }
    void showInfo(){
        QMessageBox::information(this,"Информация о файле: ",
                                 "Папка: "+dir+"\n"
                                 "Имя файла: "+filename+"\n"
                                 "Полный путь: "+adress+"\n"
                                 "Расширение: "+type);
    }
};

#endif // PAGE_H
