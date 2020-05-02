#ifndef TABLE_H
#define TABLE_H
#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QThread>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT
public:
    float coff=1;
    bool is2048created=false,is4096created=false;
    short cols,rows,** scores;
    QPushButton ***myNum;
    explicit table(QWidget *parent = 0);
    void setScore(int score,int col,int row);
    void create();
    void up(int c, int r);
    void down(int c, int r);
    void left(int c, int r);
    void right(int c, int r);
private slots:
    void on_Up_triggered();
    void on_Down_triggered();
    void on_Left_triggered();
    void on_Right_triggered();
protected:
    void keyPressEvent(QKeyEvent* ev);
    void focusOutEvent(QFocusEvent *ev);
};

#endif // TABLE_H
