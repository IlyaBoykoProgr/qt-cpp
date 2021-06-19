#include "thewindow.h"
#include "ui_thewindow.h"
#include <QScreen>

TheWindow::TheWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TheWindow)
{
    ui->setupUi(this);
    ui->intestScreen->hide();
    this->setWindowTitle(ui->LOGO->text());
    connect(ui->butt_open,SIGNAL(clicked()),this,SLOT(on_test_open_triggered()));
    connect(ui->butt_create,SIGNAL(clicked()),this,SLOT(on_test_create_triggered()));
    on_butt_research_clicked();
    iconGif = new QMovie(":/images/icon.gif");
    iconGif->setSpeed(10);
    connect(iconGif,&QMovie::frameChanged,this,&TheWindow::onFrameChanged);
    iconGif->start();
    this->resize(minimumSizeHint());
    this->show();
    {
        int realX=x();
        for(int curX=-width();curX<=realX;curX++)
           move(curX,y());
    }
}

void TheWindow::on_test_open_triggered()
{
    QUrl path=QFileDialog::getOpenFileUrl(this,"Открытие теста",QUrl(),"*.ut");
    if(path.isEmpty())return;
    openTest(path.toString().replace("file:///",""));
}

void TheWindow::openTest(QString path){
    uint64_t p_count=0,right_count=0;
    {   QFile file(path.toUtf8().data());
        file.open(QFile::ReadOnly);
        QDataStream qds(&file);
        qds>>p_count;
        ui->testProgress->setMaximum(p_count);
        ui->intestScreen->show();
        for(uint64_t i=0;i<p_count;i++){
            ui->testProgress->setValue(i);
            pagedata temp;
            temp<<qds;
            testingDialog test(this,&temp);
            test.getResultTo(right_count);
        }
        file.close();
        ui->intestScreen->hide();
    }
    if(QMessageBox::question(this,path,"Набрано "+QString::number(right_count)+" из "+QString::number(p_count)
        +"\nСохранить отчет?")==QMessageBox::Yes) saveResult(path,right_count,p_count);
}

void TheWindow::saveResult(QString path,uint64_t points, uint64_t page_count){
    QString pathsave= QFileDialog::getSaveFileUrl(this,"Выберите место сохранения",QUrl(),"*.utr",0,QFileDialog::ReadOnly)
                    .toString().replace("file:///","");
    if(pathsave.isEmpty())return;
    if(!pathsave.endsWith(".utr"))pathsave+=".utr";
    QFile file(pathsave.toUtf8().data());
    QDataStream qds(&file);
    file.open(QFile::WriteOnly);
    qds<<path<<points<<page_count;
    QMessageBox::information(this,"","Ваш результат был сохранен");
}

void TheWindow::openResult(QString path){
    QString testPath;
    {   ;
        if(path.isEmpty())return;
        QFile file(path.replace("file:///","").toUtf8().data());
        file.open(QFile::ReadOnly);
        uint64_t tempInt;
        QDataStream qds(&file);
        qds>>path>>tempInt;
        testPath="Тест был открыт в\n"+path+"\nНабрано баллов:\n"+QString::number(tempInt)+" из ";
        qds>>tempInt;
        testPath+=QString::number(tempInt);
    }
    QMessageBox::information(this,"Результат теста",testPath);
}

void TheWindow::on_result_open_triggered()
{
    QString path=QFileDialog::getOpenFileUrl(
                    0,"Открытие результата теста",QUrl(),"*.utr").toString();
    openResult(path);
}

void TheWindow::on_butt_research_clicked(){
    ui->butt_research->hide();
    ui->searchStatus->setText("Поиск существующих тестов");
    ui->listTests->clear();
std::thread([this]{
    foreach(auto file,QDir::drives()){
        QDirIterator it(file.path(),{"*.ut"},QDir::AllEntries|QDir::NoSymLinks|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
        while(it.hasNext()) ui->listTests->addItem(it.next());
    }
    ui->searchStatus->setText(ui->listTests->count()==0?"Не найдено тестов":"Созданные ранее тесты:");
    ui->butt_research->show();
}).detach();
}

void TheWindow::on_test_create_triggered()
{
    if(
       QMessageBox::question(this,"Подтверждение","Действительно хотите создать тест?")
       == QMessageBox::No
    )return;
    QString path=QFileDialog::getSaveFileUrl(this,"Выберите место сохранения",QUrl(),"*.ut").toString().replace("file:///","");
    if(path.isEmpty())return;
    uint64_t p_count=0;
    QList<pagedata> page;
    do{
        p_count++;
        pagedata cur_page;
        pageCreationDialog pcd(this);
        pcd.getTo(&cur_page);
        page.append(cur_page);
    }while(QMessageBox::question(this,"","Создать еще вопрос в тесте?")==QMessageBox::Yes);
    QFile file(path.toUtf8().data());
    file.open(QFile::WriteOnly|QFile::Truncate);
    QDataStream qds(&file);
    qds<<p_count;
    for(uint64_t i=0;i<p_count;i++) page[i]>>qds;
    file.close();
    QMessageBox::information(this,"Успех","Сохранено!");
}

void TheWindow::dropEvent(QDropEvent* event){
    QString path = event->mimeData()->urls()[0].toString().replace("file:///","");
    event->acceptProposedAction();
    if(path.endsWith(".ut")) openTest(path);
    else openResult(path);
}
void TheWindow::dragEnterEvent(QDragEnterEvent *event){
    if(!event->mimeData()->hasUrls())return;
    if(event->mimeData()->urls().count()!=1)return;
    QString path = event->mimeData()->urls()[0].toString();
    if(path.endsWith(".ut")||path.endsWith(".utr"))
        event->acceptProposedAction();
}
void TheWindow::on_listTests_itemDoubleClicked(QListWidgetItem *item){
    if(
        QMessageBox::question(this,"","Открыть тест "+item->text()+"?")==QMessageBox::No
    )return;
    openTest(item->text());
}

TheWindow::~TheWindow(){
    delete ui;
}

