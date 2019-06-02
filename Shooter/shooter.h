#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
  class shooter;
}

class shooter : public QMainWindow
{
  Q_OBJECT

public:
  explicit shooter(QWidget *parent = 0);
  ~shooter();
  void keyPressEvent(QKeyEvent* ev);

public slots:
  void shoot(int x);
signals:
  void pif_paf(int x);
private:
  Ui::shooter *ui;
};

#endif // SHOOTER_H
