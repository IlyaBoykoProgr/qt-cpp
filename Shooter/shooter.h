#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  Ui::shooter *ui;
  short rushed=0;
  explicit shooter(QWidget *parent = 0);
  ~shooter();

public slots:
  void shoot(int x);
  void unlockAch(int broken);
  void keyPressEvent(QKeyEvent* ev);
  void on_actionNew_Game_triggered();
signals:
  void pif_paf(int x);
private slots:
  void on_actionAchievements_triggered();

  void on_actionProgress_triggered();

  void on_actionChange_blocks_triggered();
  void on_actionQuit_triggered();

private:
  block** kirpich;
};

#endif // SHOOTER_H
