#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include "ui_shooter.h"
class block;

namespace Ui {
  class shooter;
}
class shooter : public QMainWindow{
  Q_OBJECT
public:
  Ui::shooter *ui;
  block** kirpich;
  int rushed=0;
  int BLOCKS;
  explicit shooter(QWidget *parent = 0);
  ~shooter();

public slots:
  void unlockAch(int broken);
  void keyPressEvent(QKeyEvent* ev);
  void timerEvent(QTimerEvent *ev);
  void on_actionNew_Game_triggered();
signals:
  void pif_paf(int x);
private slots:
  void on_actionAchievements_triggered();
  void on_actionProgress_triggered();
  void on_actionChange_blocks_triggered();
  void on_actionQuit_triggered();
  void on_actionPause_triggered();
};

#endif // SHOOTER_H
