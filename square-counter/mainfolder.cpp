#include "mainfolder.h"
#include "ui_mainfolder.h"

MainFolder::MainFolder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainFolder)
{
    ui->setupUi(this);
    connect(ui->val_a,SIGNAL(valueChanged(double)),this,SLOT(on_val_a_b_c_changed()));
    connect(ui->val_b,SIGNAL(valueChanged(double)),this,SLOT(on_val_a_b_c_changed()));
    connect(ui->val_c,SIGNAL(valueChanged(double)),this,SLOT(on_val_a_b_c_changed()));
}

MainFolder::~MainFolder()
{
    delete ui;
}

void MainFolder::on_val_a_b_c_changed()
{
    long timeBefore=clock();
    double a=ui->val_a->value(),b=ui->val_b->value(),c=ui->val_c->value(),d=0;
    ui->ABCshow->setText("a="+toTxt(a)+" b="+toTxt(b)+" c="+toTxt(c));
    d=b*b-4*a*c;
    if(d<0){
        ui->x1x2show->setText("Нет корней");
    }else if(d==0){
        ui->x1x2show->setText("x=0");
    }else{
        double x1=(-b-sqrt(d))/(2*a);
        double x2=(-b+sqrt(d))/(2*a);
        ui->x1x2show->setText("x1= "+toTxt(x1)+", x2= "+toTxt(x2));
    }
    this->setWindowTitle("Решалка: решено за "+toTxt(clock()-timeBefore)+" миллисекунд!");
}
