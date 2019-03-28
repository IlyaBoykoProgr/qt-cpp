#ifndef WIND_H
#define WIND_H

#include <QMainWindow>
namespace Ui {
class wind;
}

class wind : public QMainWindow
{
    Q_OBJECT

public:
    explicit wind(QWidget *parent = 0);
    Ui::wind *ui;
    ~wind();

private slots:
    void on_action_triggered();
    void paintEvent(QPaintEvent *event);
};

#endif // WIND_H
