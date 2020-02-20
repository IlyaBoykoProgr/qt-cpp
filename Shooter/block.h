#ifndef BLOCK_H
#define BLOCK_H

#include "shooter.h"
#include "database.h"
#include <QLabel>
class block: public QLabel{
  Q_OBJECT
  short health;
public:
  block(int x, int y,short health,shooter* parent);
  void hit();
public slots:
  void update();
signals:
  void achieve(int);
};

#endif // BLOCK_H
