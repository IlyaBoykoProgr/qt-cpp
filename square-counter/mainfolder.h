#ifndef MAINFOLDER_H
#define MAINFOLDER_H

#include <QMainWindow>
#include <math.h>
#include <ctime>
#define toTxt(n) QString::number(n)

QT_BEGIN_NAMESPACE
namespace Ui { class MainFolder; }
QT_END_NAMESPACE

class MainFolder : public QMainWindow
{
    Q_OBJECT

public:
    MainFolder(QWidget *parent = nullptr);
    ~MainFolder();

private slots:
    void on_val_a_b_c_changed();

private:
    Ui::MainFolder *ui;
};
#endif // MAINFOLDER_H
