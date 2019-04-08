#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    ~table();
private:
    Ui::table *ui;
    QPushButton* nums[4][4];
};

#endif // TABLE_H
