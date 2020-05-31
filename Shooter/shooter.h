#ifndef SHOOTER_H
#define SHOOTER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QProgressBar>
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
  QProgressBar* progress;
  int rushed=0;
  int BLOCKS;
  explicit shooter(QWidget *parent = 0);
  ~shooter();

public slots:
  void unlockAch(int broken);
  void keyPressEvent(QKeyEvent* ev);
  void timerEvent(QTimerEvent *ev);
  void on_actionNew_Game_triggered();
  void on_actionAchievements_triggered();
  void on_actionProgress_triggered();
  void on_actionChange_blocks_triggered();
  void on_actionPause_triggered();
signals:
  void pif_paf(int x);
};

#endif // SHOOTER_H
