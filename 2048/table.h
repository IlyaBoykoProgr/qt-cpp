#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QKeyEvent>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void create();
    ~table();
private slots:
    void on_Up_triggered();
    void on_Down_triggered();
    void on_Left_triggered();
    void on_Right_triggered();

private:
    Ui::table *ui;
};

#endif // TABLE_H
