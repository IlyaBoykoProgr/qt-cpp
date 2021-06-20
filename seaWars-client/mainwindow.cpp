#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->act_EndPlacing->setDisabled(true);
    ui->act_Shoot->setVisible(false);
    field1= new Field(this,40,72);
    field2= new Field(this,262,72);
    field2->isEnemyField= true;
    field1->isEnemyField= false;
}

void MainWindow::on_act_server_triggered()
{
    connect(field2,SIGNAL(clicked()),this,SLOT(field2_clicked()));
    if(socket!=0)delete socket;
    socket= new Client;
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::onGameEnd);
    connect(socket,&Client::youWereShooted,this,&MainWindow::Shoot_recieved);
    connect(socket,&Client::youHitted,this,&MainWindow::hitted);
    connect(socket,&Client::youMissed,this,&MainWindow::missed);
    connect(socket,&Client::newMessage,this,&MainWindow::addMessage);
    field1->setEnabled(true);
    ui->act_EndPlacing->setEnabled(socket->isOpen());
    setWindowIcon(QIcon(socket->isOpen()?":/images/boat.png":":/images/miss.png"));
    if(socket->index==1){
        setDisabled(true);
        while(!socket->waitForReadyRead(1000));
        setEnabled(true);
    }
    if(socket->isOpen()){
        ui->pin->setNum(socket->gamePin);
    }
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
    field1->setDisabled(true);
    socket->write("ready");
    State= socket->index==2?ST_ATTACK:ST_PROTECT;
    if(State==ST_ATTACK){
        addMessage("Ваша очередь стрелять,\n выберите клетку на карте\n противника и нажмите 'Стрелять'");
    }
    if(State==ST_PROTECT){
        addMessage("Вас будут атаковать!");
        ui->act_Shoot->setDisabled(true);
    }
}

void MainWindow::on_act_Shoot_triggered()
{
    if(field2->isEmpty(field2->clickX,field2->clickY))
       socket->write(("shoot "+QString::number(field2->clickX)+" "+QString::number(field2->clickY)) .toStdString().c_str());
    else{
        addMessage("Здесь нельзя стрелять,\n клетка уже известна!");
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
    box->setGeometry(150,50*msg_count,300,50);
    box->show();
    box->raise();
    msg_count++;
    std::thread([this,box]{
        this_thread::sleep_for(chrono::seconds(2));
        box->deleteLater();
        msg_count--;
    }).detach();
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

void MainWindow::onGameEnd(){
    ui->pin->clear();
    QApplication::exit(
        QMessageBox::warning(this,"Внимание!","Вы отключились от сервера!\nИграть заново?",QMessageBox::Reset|QMessageBox::No)
        ==QMessageBox::Reset
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}
