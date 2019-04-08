#include "table.h"
#include "ui_table.h"
#include <QThread>

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        nums[r][c]= new QPushButton("",ui->centralWidget);
        ui->gridLayout->addWidget(nums[r][c],r,c);
        nums[r][c]->setMinimumHeight(nums[r][c]->width());
    }
}

void table::paintEvent(QPaintEvent *e){
    for(int r=0; r<4; r++)for(int c=0; c<4; c++){
        QPushButton* now= nums[r][c];
        now->resize(now->width(),now->width());
    }
}

table::~table()
{
    delete ui;
}
