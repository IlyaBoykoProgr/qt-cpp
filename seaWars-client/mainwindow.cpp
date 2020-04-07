#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();
    field1= new Field(this,40,72);
    field2= new Field(this,262,72);
    field2->clickable= false;
    field1->clickable=false;
}

void MainWindow::on_act_NewGame_triggered()
{
    connect(field2,SIGNAL(clicked()),this,SLOT(field2_clicked()));
    if(!socket)delete socket;
    socket= new Client;
    connect(socket,SIGNAL(disconnected()),this,SLOT(on_act_NewGame_triggered()));
    connect(socket,SIGNAL(youWereShooted(int,int)),this,SLOT(Shoot_recieved(int,int)));
    connect(socket,SIGNAL(youHitted()),this,SLOT(hitted()));
    connect(socket,SIGNAL(youMissed()),this,SLOT(missed()));
    ui->toolBar->setVisible(socket->isOpen());
    ui->act_Shoot->setVisible(false);
    field1->clickable=true;
    State= ST_PLACE;
}

void MainWindow::on_act_EndPlacing_triggered()
{
    if(field1->getCode().count('1')!=20){
        QMessageBox::information(this,"Чую подставу...","Ну видно же, что корабли стоят неправильно");
        return;
    }
    ui->act_EndPlacing->setVisible(false);
    ui->act_Shoot->setVisible(true);
    field1->clickable=false;
    socket->write("ready ");
    socket->write(field1->getCode().toStdString().c_str());
    State= socket->index==1?ST_ATTACK:ST_PROTECT;
    if(State==ST_ATTACK){
        ui->statusbar->showMessage("Ваша очередь стрелять, выберите клетку на карте противника и нажмите 'Стрелять'");
    }
    if(State==ST_PROTECT){
        ui->statusbar->showMessage("Вас будут атаковать");
        ui->act_Shoot->setDisabled(true);
    }
}

void MainWindow::on_act_Shoot_triggered()
{
    if(field2->isEmpty(field2->clickX,field2->clickY))
       socket->write(("shoot "+QString::number(field2->clickX)+" "+QString::number(field2->clickY)).toStdString().c_str());
    else{
        QMessageBox::critical(this,"Вы ошиблись!","Здесь нельзя стрелять, клетка уже известна!");
        return;
    }
    ui->act_Shoot->setDisabled(true);
    State=ST_PROTECT;
}
void MainWindow::hitted(){field2->setBoat(field2->clickX,field2->clickY,CL_BOAT);
                         ui->statusbar->showMessage("Вы попали!");}
void MainWindow::missed(){field2->setBoat(field2->clickX,field2->clickY,CL_MISS);
    ui->statusbar->showMessage("Вы промазали..");}

void MainWindow::Shoot_recieved(int x, int y){
    socket->write(field1->isABoat(x,y)?"hit":"miss");
    ui->statusbar->showMessage("Вы атакуете");
    ui->act_Shoot->setDisabled(false);
    State=ST_ATTACK;
}

void MainWindow::field2_clicked(){
    if(State!=ST_ATTACK)return;
    QString message="Текущая клетка: ";
    switch(field2->clickX+1){
    case 1:message+="А";break;
    case 2:message+="Б";break;
    case 3:message+="В";break;
    case 4:message+="Г";break;
    case 5:message+="Д";break;
    case 6:message+="Е";break;
    case 7:message+="Ж";break;
    case 8:message+="З";break;
    case 9:message+="И";break;
    case 10:message+="К";break;
    }
    ui->statusbar->showMessage(message+" "+QString::number(field2->clickY+1));
}

MainWindow::~MainWindow()
{
    delete ui;
}
