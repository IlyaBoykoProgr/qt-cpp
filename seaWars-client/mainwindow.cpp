#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
using namespace std;

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
    if(socket!=0)delete socket;
    socket= new Client();
    connect(socket,SIGNAL(disconnected()),this,SLOT(on_act_NewGame_triggered()));
    connect(socket,SIGNAL(youWereShooted(int,int)),this,SLOT(Shoot_recieved(int,int)));
    connect(socket,SIGNAL(youHitted()),this,SLOT(hitted()));
    connect(socket,SIGNAL(youMissed()),this,SLOT(missed()));
    connect(socket,SIGNAL(newMessage(QString)),this,SLOT(addMessage(QString)));
    ui->toolBar->setVisible(socket->isOpen());
    setWindowIcon(QIcon(socket->isOpen()?":/images/boat.png":":/images/miss.png"));
    ui->act_Shoot->setVisible(false);
    field1->clickable=true;
    State= ST_PLACE;
}

void MainWindow::on_act_EndPlacing_triggered()
{
    if(field1->getCode().count('1')!=20){
        addMessage("Корабли стоят неправильно");
        return;
    }
    ui->act_EndPlacing->setVisible(false);
    ui->act_Shoot->setVisible(true);
    field1->clickable=false;
    socket->write("ready ");
    socket->write(field1->getCode().toStdString().c_str());
    State= socket->index==1?ST_ATTACK:ST_PROTECT;
    if(State==ST_ATTACK){
        addMessage("Ваша очередь стрелять,\n выберите клетку на карте\n противника и нажмите 'Стрелять'");
    }
    if(State==ST_PROTECT){
        QMessageBox::warning(this,"Ой-ей!","Вас будут атаковать!");
        ui->act_Shoot->setDisabled(true);
    }
}

void MainWindow::on_act_Shoot_triggered()
{
    if(field2->isEmpty(field2->clickX,field2->clickY))
       socket->write(("shoot "+QString::number(field2->clickX)+" "+QString::number(field2->clickY)) .toStdString().c_str());
    else{
        QMessageBox::critical(this,"Вы ошиблись!","Здесь нельзя стрелять,\n клетка уже известна!");
        return;
    }
}
void MainWindow::hitted(){
    field2->setBoat(field2->clickX,field2->clickY,CL_BOAT);
    addMessage("Вы попали! За это вы\n можете ещё раз стрелять.");
    if(field2->getCode().count('1')==20){
        addMessage("Победааа!!!!\nКорабли противника уничтожены!");
    }
    State=ST_ATTACK;
}
void MainWindow::missed(){
    field2->setBoat(field2->clickX,field2->clickY,CL_MISS);
    addMessage("Вы промазали..");
    ui->act_Shoot->setDisabled(true);
    State=ST_PROTECT;
}

void MainWindow::Shoot_recieved(int x, int y){
    socket->write(field1->isABoat(x,y)?"hit":"miss");
    if(field1->isABoat(x,y)){
        field1->setBoat(x,y,CL_DESTROYED);
        addMessage("Противник бьёт ещё раз,\n потому что он попал!");
        if(field1->getCode().count('2')==20){
            addMessage("Противник уничтожил ваши корабли\nВы проиграли.\nНичего, еще выиграете!");
        }
    }
    else{
        field1->setBoat(x,y,CL_MISS);
        addMessage("Ура! Вы атакуете, по вашим\n кораблям не попали!");
        ui->act_Shoot->setDisabled(false);
        State=ST_ATTACK;
    }
}

void MainWindow::addMessage(QString msg){
    QLabel* box= new QLabel(msg,this);
    box->setStyleSheet("background:lightblue");
    box->setAlignment(Qt::AlignCenter);
    QGraphicsOpacityEffect* oeff=new QGraphicsOpacityEffect(this);
    connect(oeff,SIGNAL(opacityChanged(qreal)),this,SLOT(repaint()));
    oeff->setOpacity(0.0);
    box->setGraphicsEffect(oeff);
    box->setGeometry(150,42*msg_count,200,40);
    box->show();
    box->raise();
    msg_count++;
    std::thread th([this,box,oeff]{
        this_thread::sleep_for(2s);
        box->deleteLater();
        msg_count--;
    });
    th.detach();
}

void MainWindow::on_msg_edit_returnPressed()
{
    if(socket==0|| !socket->isOpen())return;
    QString msg=ui->msg_edit->text();
    ui->msg_edit->clear();
    msg="msg "+msg;
    socket->write(msg.toStdString().c_str());
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
