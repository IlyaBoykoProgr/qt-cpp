#ifndef PAGECREATIONDIALOG_H
#define PAGECREATIONDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "testData.h"

namespace Ui {
class pageCreationDialog;
}

class pageCreationDialog : public QDialog
{
    Q_OBJECT
public slots:
    void getTo(pagedata* data);
public:
    explicit pageCreationDialog(QWidget *parent = nullptr);
    ~pageCreationDialog();

private slots:
    void on_page_type_currentIndexChanged(int index);
    void on_butt_addAnswer_clicked();
    void on_butt_done_clicked();
    void on_list_answers_itemDoubleClicked(QListWidgetItem *item);
    void on_list_answers_itemClicked(QListWidgetItem *item);

private:
    QList<bool> isRight;
    page_type cur_type;
    QList<QString> answ_vars;
    Ui::pageCreationDialog *ui;
};

#endif // PAGECREATIONDIALOG_H
