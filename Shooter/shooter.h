#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>

namespace Ui {
  class shooter;
}

class shooter : public QMainWindow
{
  Q_OBJECT

public:
  explicit shooter(QWidget *parent = 0);
  ~shooter();

private:
  Ui::shooter *ui;
};

#endif // SHOOTER_H
