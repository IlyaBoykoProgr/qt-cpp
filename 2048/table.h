#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    int short scores[4][4];
    QLabel *myNum[4][4];
    explicit table(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void setScore(int score,int col,int row);
    void create();
    void up(int c, int r);
    void down(int c, int r);
    void left(int c, int r);
    void right(int c, int r);
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
