#include "opener.h"
#include "ui_opener.h"
#include <QMessageBox>
#include <QMimeDatabase>
#include <QFile>

opener::opener(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::opener)
{
    ui->setupUi(this);
    documents=new QFileSystemModel(this);
    documents->setRootPath("/");
    ui->files->setModel(documents);
    ui->label->hide();
}

opener::~opener()
{
    delete ui;
}

void opener::on_files_doubleClicked(const QModelIndex &index)
{
    if(documents->isDir(index)){
        ui->statusBar->clearMessage();
        return;
    }
    if(!documents->fileInfo(index).isReadable()){
        QMessageBox::critical(this,"Error","Can't read this file!");
        return;
    }
    QMimeDatabase* db=new QMimeDatabase;
    QString which=db->mimeTypeForFile(documents->fileInfo(index),QMimeDatabase::MatchContent).name();
    delete db;
    ui->statusBar->showMessage(which);
    if(which.contains("text/")){
        QFile file(documents->fileInfo(index).absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QLabel view(QString(file.readAll()),this);view.show();
    }
}

void opener::textopen(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    ui->label->setText(file.readAll());
    ui->label->show();
}
