#ifndef TABLE_H
#define TABLE_H
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT
public:
    float coff=1;
    short cols;
    short rows;
    short** scores;
    QPushButton ***myNum;
    explicit table(QWidget *parent = 0);
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
