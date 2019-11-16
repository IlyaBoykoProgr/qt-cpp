#ifndef BLOCK_H
#define BLOCK_H

#include "shooter.h"
#include "database.h"
#include <QLabel>
class block: public QLabel{
  Q_OBJECT
  short h;
public:
  block(int x, int y,short health,shooter* parent);
  void destroy();
public slots:
  void update();
signals:
  void achieve(int);
};

#endif // BLOCK_H
