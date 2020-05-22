#include "notepad.h"
#include "page.h"
#include <QProcess>
#define currentPage ((Page*)(files->currentWidget()))

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    files= new QTabWidget(this);
    files->setMovable(true);
    files->setTabsClosable(true);
    ui->verticalLayout->addWidget(files);
    connect(files,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab()));
    show();
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_act_New_triggered()
{
    new Page(files);
    anim();
    ui->statusbar->showMessage("Создан новый документ");
}

void Notepad::on_act_Save_triggered()
{
    if(files->count()==0)return;
    while(!currentPage->save()){
        if(QMessageBox::critical(this,"Ошибка!","Не удалось сохранить файл\nПопробовать еще раз?",
           QMessageBox::Retry,QMessageBox::No)==QMessageBox::No)return;
        ui->statusbar->showMessage("Файл не сохранен");animErr();
    }
    ui->statusbar->showMessage("Файл сохранен");
    anim();
}

void Notepad::on_act_Open_triggered()
{
    Page* p=new Page(files);
    p->open(
         QFileDialog::getOpenFileUrl(this,"Выберите файл для открытия")
    );
    anim();
    if(p->adress.isEmpty()){
        delete p;
        ui->statusbar->showMessage("Вкладка не открыта: файл не выбран");
    }else
        ui->statusbar->showMessage("Документ "+files->tabText(p->index)+" открыт");
}

void Notepad::on_act_Remove_triggered()
{
    if(files->count()==0)return;
    if(QMessageBox::question(this,"Подтверждение","Вы действительно хотите удалить "+currentPage->filename+" ?")
            ==QMessageBox::Yes){
        remove(currentPage->adress.toStdString().c_str());
        delete currentPage;
        ui->statusbar->showMessage("Документ удален");anim();
    }else{
        ui->statusbar->showMessage("Документ не удален");animErr();
    }
}

void Notepad::on_act_NoSave_triggered()
{
    if(files->count()==0)return;
    Page* cur=(Page*)(files->currentWidget());
    ui->statusbar->showMessage("Вкладка закрыта безвозвратно");
    delete cur;
}

void Notepad::on_act_NewWindow_triggered()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    anim();
}

void Notepad::on_act_Rename_triggered()
{
    if(files->count()==0)return;
    if(currentPage->rename()){
        ui->statusbar->showMessage("Файл успешно переименован");
        anim();
    }
    else{animErr();
        QMessageBox::critical(this,"Ошибка","Файл не получилось переименовать");
        ui->statusbar->showMessage("Файл не переименован");
    }
}

void Notepad::on_act_Info_triggered()
{
    anim();
    currentPage->showInfo();
}

void Notepad::on_act_Restart_triggered()
{
    anim();
    on_act_NewWindow_triggered();
    QApplication::exit();
}


void Notepad::closeTab(){
    if(!files->isTabEnabled(currentPage->index)){
        on_act_NoSave_triggered();return;
    }
    if(currentPage->isSaved()==false)
    switch(QMessageBox::question(this,"Закрытие вкладки","Вы пытаетесь закрыть вкладку\nСохранить документ?",
           QMessageBox::Yes,QMessageBox::No,QMessageBox::Cancel)){
        case QMessageBox::Cancel:return;
        case QMessageBox::Yes: on_act_Save_triggered(); break;
        case QMessageBox::No: break;
    }
    on_act_NoSave_triggered();
}

void Notepad::on_act_About_triggered()
{
    QMessageBox::about(this,"Сначала о фреймворке","Написано на C++ с помощью...");
    QMessageBox::aboutQt(this,"Этого фреймворка");
    QMessageBox::about(this,"Об авторе)","Это произведение искусства написано юным программистом\n"
                                         "Мои соц.сети: \n"
                                         "VK: http://vk.com/ilya.boyko\n"
                                         "Discord: @Iluha168\n"
                                         "Telegram:@IlyaBoykoProgr\n"
                                         "GitHub:http://github.com/IlyaBoykoProgr\n"
                                         "Дальше не буду");
}

void Notepad::closeEvent(QCloseEvent* event){
    if(files->count()!=0&& QMessageBox::question(this,
           "Внимание!","Не все вкладки закрыты.\n"
           "Действительно закрыть приложение?")==QMessageBox::No){
        event->ignore();animErr();
    }else{
        event->accept();anim();
    }
}
