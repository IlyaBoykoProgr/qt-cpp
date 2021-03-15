#include "mainview.h"
#include <windows.h>
#include <string>
using std::string;

MainView::MainView(QWidget *parent) : QMainWindow(parent){
    ui->setupUi(this);
    show();
    ui->progress->setMaximum(0xffffff);
    on_showVisible_stateChanged(true);
}

void MainView::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/3*2-40);
    ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/3-40);
}

void MainView::on_showVisible_stateChanged(int on){
    ui->progress->show();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Заголовок"<<"Класс");
    wchar_t className[100], title[100];
    for(HWND wnd=0;(UINT_PTR)wnd<=65536;wnd++){
        if((UINT_PTR)wnd%(int)0xffff==0){
            ui->progress->setValue((UINT_PTR)wnd);
            repaint();
        }
        if(!IsWindow(wnd))continue;
        if(on&&!IsWindowVisible(wnd))continue;

        int row=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for(int i=0;i<100;i++){className[i]=0;title[i]=0;}
        GetWindowTextW(wnd,title,100);
        GetClassNameW(wnd,className,100);

        ui->tableWidget->setVerticalHeaderItem(row,new
            QTableWidgetItem(QString::number((UINT_PTR)wnd))
        );
        ui->tableWidget->setCellWidget(row,0,new
            QLabel(QString::fromWCharArray(title,100))
        );
        ui->tableWidget->setCellWidget(row,1,new
            QLabel(QString::fromWCharArray(className,100))
        );
    }
    ui->progress->hide();
}

void MainView::on_tableWidget_cellDoubleClicked(int row, int col){
    Q_UNUSED(col);
    int window=ui->tableWidget->verticalHeaderItem(row)->text().toInt();
    (new InfoWindow(window))->show();
}

void MainView::on_refresh_clicked(){
    on_showVisible_stateChanged(ui->showVisible->isChecked());
}
