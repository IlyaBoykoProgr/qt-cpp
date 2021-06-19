#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include <QListWidgetItem>
#include "testData.h"

namespace Ui {
class testingDialog;
}

class testingDialog : public QDialog{
    Q_OBJECT
public:
    testingDialog(QWidget *parent = nullptr,pagedata* g=nullptr);
    ~testingDialog();
public slots:
    void getResultTo(uint64_t& true_count);
private slots:
    void on_butt_next_clicked();

private:
    pagedata* data;
    Ui::testingDialog *ui;
};

#endif // TESTINGDIALOG_H
