#include "shooter.h"
#include "ui_shooter.h"

shooter::shooter(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::shooter)
{
  ui->setupUi(this);
}

shooter::~shooter()
{
  delete ui;
}
