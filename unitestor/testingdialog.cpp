#include "testingdialog.h"
#include "ui_testingdialog.h"

testingDialog::testingDialog(QWidget *parent,pagedata* g) :
    QDialog(parent),
    ui(new Ui::testingDialog)
{
    ui->setupUi(this);
    data=g;
    ui->l_question->setText(data->question);
    if(data->type==INPUT){
        ui->form->hide();
        ui->l_tip->setText("Введите свой ответ в поле ниже:");
    }else ui->form_input->hide();
    if(data->type==RADIO){
        ui->l_tip->setText("Выберите один вариант ответа:");
        foreach(QString str,data->variants){
            QListWidgetItem *qlwi= new QListWidgetItem(ui->form);
            ui->form->setItemWidget(qlwi, new QRadioButton(str));
        }
    }
    if(data->type==CHECKBOX){
        ui->l_tip->setText("Выберите ответы, которые считаете верными:");
        foreach(QString str,data->variants){
            QListWidgetItem *qlwi= new QListWidgetItem(ui->form);
            ui->form->setItemWidget(qlwi, new QCheckBox(str));
        }
    }
    adjustSize();
}

void testingDialog::getResultTo(uint64_t& true_count){
    begin:
    exec();
    if(result()==Rejected)goto begin;
    if(data->type==INPUT){
        foreach(QString answer, data->variants)
        if(answer==ui->form_input->text()){
                true_count++;
                return;
        }
    }
    if(data->type==RADIO)for(int i=0;i<ui->form->count(); i++){
        QRadioButton* curr=(QRadioButton*)ui->form->itemWidget(ui->form->item(i));
        if(curr->isChecked()&&data->isAnswer[i]){
            true_count++;
            return;
        }
    }
    if(data->type==CHECKBOX){
        int right_checked=0;
        for(int i=0;i<ui->form->count();i++){
            QCheckBox* curr=(QCheckBox*)ui->form->itemWidget(ui->form->item(i));
            if(data->isAnswer[i]==curr->isChecked())right_checked++;
        }
        if(right_checked==data->variants.count())true_count++;
    }
}

testingDialog::~testingDialog(){delete ui;}

void testingDialog::on_butt_next_clicked()
{
    close();
    setResult(Accepted);
}
