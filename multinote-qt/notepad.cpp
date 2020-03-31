#include "notepad.h"
#include "page.h"
#include <QProcess>

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
    on_act_Open_triggered();
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_act_New_triggered()
{
    new Page(files);
    ui->statusbar->showMessage("Создан новый документ");
}

void Notepad::on_act_Save_triggered()
{
    if(files->count()==0)return;
    Page* cur=(Page*)(files->currentWidget());
    while(!cur->save()){
        if(QMessageBox::critical(this,"Ошибка!","Не удалось сохранить файл\nПопробовать еще раз?",
           QMessageBox::Retry,QMessageBox::No)==QMessageBox::No)return;
        ui->statusbar->showMessage("Файл не сохранен");
    }
    cur->open(cur->adress);
    ui->statusbar->showMessage("Файл сохранен");
}

void Notepad::on_act_Open_triggered()
{
    Page* p=new Page(files);
    p->open(
         QFileDialog::getOpenFileUrl(this,"Выберите файл для открытия")
    );
    if(p->adress.isEmpty()){
        delete p;
        ui->statusbar->showMessage("Вкладка не открыта: файл не выбран");
    }else
        ui->statusbar->showMessage("Документ "+files->tabText(p->index)+" открыт");
}

void Notepad::on_act_Remove_triggered()
{
    if(files->count()==0)return;
    Page* cur=(Page*)(files->currentWidget());
    if(QMessageBox::question(this,"Подтверждение","Вы действительно хотите удалить "+files->tabText(cur->index)+" ?")
            ==QMessageBox::Yes){
        remove(cur->adress.toStdString().c_str());
        delete cur;
        ui->statusbar->showMessage("Документ удален");
    }else{
        ui->statusbar->showMessage("Докмент не удален");
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
}

void Notepad::on_act_Rename_triggered()
{
    if(((Page*)(files->currentWidget()))->rename())
        ui->statusbar->showMessage("Файл успешно переименован");
    else{
        QMessageBox::critical(this,"Ошибка","Файл не получилось переименовать");
        ui->statusbar->showMessage("Файл не переименован");
    }
}

void Notepad::on_act_Info_triggered()
{
    ((Page*)(files->currentWidget()))->showInfo();
}

void Notepad::on_act_Restart_triggered()
{
    on_act_NewWindow_triggered();
    QApplication::exit();
}


void Notepad::closeTab(){
    if(!files->isTabEnabled(((Page*)(files->currentWidget()))->index)){
        on_act_NoSave_triggered();return;
    }
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
                                         "Discord: @IlyaBoyko\n"
                                         "Telegram:@IlyaBoykoProgr\n"
                                         "GitHub:http://github.com/IlyaBoykoProgr\n"
                                         "Дальше не буду");
}

void Notepad::closeEvent(QCloseEvent* event){
    event->accept();
    if(files->count()!=0&& QMessageBox::question(this,
           "Внимание!","Не все вкладки закрыты.\n"
           "Действительно закрыть приложение?")==QMessageBox::No)
    event->ignore();
}
