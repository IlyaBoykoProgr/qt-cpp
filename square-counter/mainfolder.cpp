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
    d=b*b-4*a*c;
    ui->ABCshow->setText("a="+toTxt(a)+" b="+toTxt(b)+" c="+toTxt(c)+" => D= ("
                         +toTxt(b)+")²-4*("+toTxt(a)+")*("+toTxt(c)+") = "+toTxt(d));
    if(d<0){
        ui->x1show->setText("Нет корней");
        ui->x2show->clear();
    }else if(d==0){
        ui->x1show->setText("x=0");
        ui->x2show->clear();
    }else{
        double x1=(-b-sqrt(d))/(2*a);
        double x2=(-b+sqrt(d))/(2*a);
        if      ((int)x1==x1){
            ui->x1show->setText("x1= "+toTxt(x1));
        }else{
            QString x1str;
            if((int)sqrt(d)==sqrt(d)){
                x1str="       "+toTxt(-b-sqrt(d))+"\nx1=------\n       "+toTxt(2*a);
            }else
                x1str="       "+toTxt(-b)+"-√"+toTxt(d)+"\nx1=------\n       "+toTxt(2*a);
            ui->x1show->setText(x1str);
        }
        if((int)x2==x2){
            ui->x2show->setText("x2= "+toTxt(x2));
        }else{
            QString x2str;
            if((int)sqrt(d)==sqrt(d)){
                x2str="       "+toTxt(-b+sqrt(d))+"\nx1=------\n       "+toTxt(2*a);
            }else
                x2str="       "+toTxt(-b)+"-√"+toTxt(d)+"\nx1=------\n       "+toTxt(2*a);
            ui->x1show->setText(x2str);
        }
    }
    this->setWindowTitle("Решалка: решено за "+toTxt(clock()-timeBefore)+" миллисекунд!");
}
