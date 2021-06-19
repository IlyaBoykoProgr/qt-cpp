#include "pagecreationdialog.h"
#include "ui_pagecreationdialog.h"

pageCreationDialog::pageCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pageCreationDialog)
{
    ui->setupUi(this);
    ui->page_type->addItems(QStringList()<<"Открытый вопрос"<<"Один вариант ответа"<<"Несколько ответов");
    on_page_type_currentIndexChanged(0);
}

void pageCreationDialog::getTo(pagedata* data){
    begin:
    exec();
    if(result()==Rejected)goto begin;
    if(ui->page_type->currentIndex()==-1){
        QMessageBox::critical(this,"Ошибка","Вы не выбрали тип теста");
        goto begin;
    }
    if(ui->question->toPlainText().isEmpty()){
        QMessageBox::critical(this,"Ошибка","Не задан сам вопрос");
        goto begin;
    }
    if(answ_vars.empty()){
        QMessageBox::critical(this,"Ошибка","Нет вариантов ответа");
        goto begin;
    }
    if(cur_type!=INPUT&&isRight.count(1)==0){
        QMessageBox::critical(this,"Ошибка","Вы не выбрали ни одного правильного ответа\nПодсказка: нажмите по варианту ответа, чтобы сделать его верным/неверным");
        goto begin;
    }
    if(cur_type==RADIO&&isRight.count(1)>1){
        QMessageBox::warning(this,"Ошибка","Вы выбрали режим 'один ответ',\nно верных ответов более одного!");
        goto begin;
    }
    data->type=(page_type)ui->page_type->currentIndex();
    data->variants=answ_vars;
    data->isAnswer=isRight;
    data->question=ui->question->toPlainText();
}

void pageCreationDialog::on_page_type_currentIndexChanged(int index){
    cur_type=(page_type)index;
    if(index==0) ui->tip_3->setText("Открытый вопрос - тестируемому будет отображено поле ввода.\n"
                                    "Варианты ответа выведены не будут. Балл за вопрос будет получен,\n"
                                    "если тестируемый введет в поле любой из вариантов ответа.\n"
                                    "Варианты ответа можно задать ниже (Регистр учитывается):");
    else if(index==1) ui->tip_3->setText("Один вариант ответа - тестируемый сможет выбрать только\n"
                                         "один ответ из списка вариантов. Балл будет получен,\n"
                                         "если выбранный вариант верен. (Верный вариант может быть только один)");
    else if(index==2) ui->tip_3->setText("Несколько ответов - тестируемый сможеть выбрать несколько ответов.\n"
                                         "Список вариантов будет виден. Чтобы получить балл за вопрос,\n"
                                         "тестируемый должен отметить все верные варианты и ни одного неверного.");
}

void pageCreationDialog::on_butt_addAnswer_clicked()
{
    if(ui->answer_input->text().isEmpty())return;
    answ_vars.append(ui->answer_input->text());
    isRight.append(0);
    ui->list_answers->addItem(ui->answer_input->text());
    ui->answer_input->clear();
    ui->list_answers->item(ui->list_answers->count()-1)->setBackground(
        QBrush(isRight[ui->list_answers->count()-1]?Qt::green:Qt::red));
    //previous line sets green|red color to true|false answer
}

void pageCreationDialog::on_butt_done_clicked()
{
    close();
    setResult(Accepted);
}

void pageCreationDialog::on_list_answers_itemDoubleClicked(QListWidgetItem *item)
{
    if(QMessageBox::question(this,"","Удалить ответ '"+item->text()+"'?")==QMessageBox::No)return;
    answ_vars.removeAt(ui->list_answers->row(item));
    isRight.removeAt(ui->list_answers->row(item));
    ui->list_answers->takeItem(ui->list_answers->row(item));
}

void pageCreationDialog::on_list_answers_itemClicked(QListWidgetItem *item)
{
    isRight[ui->list_answers->row(item)]=
   !isRight[ui->list_answers->row(item)];
    item->setBackground(QBrush(isRight[ui->list_answers->row(item)]?Qt::green:Qt::red));
    ui->list_answers->clearSelection();
}

pageCreationDialog::~pageCreationDialog(){delete ui;}
