#include "block.h"

block::block(int x, int y,short health,shooter* parent)
{
    setFont(QFont("Aerial",20));
    setAlignment(Qt::AlignCenter);
    setParent(parent);
    connect(parent,SIGNAL(pif_paf(int)),this,SLOT(update()));
    setGeometry(x,y,100,40);
    show();
    this->health=health+1;
    hit();
}

void block::hit(){
  if(health<=1){
   move(-300,0);
   bin::set(bin::brokenBlocks()+1);
   ((shooter*)parent())->rushed++;
   emit achieve(bin::brokenBlocks());
  }else{
  health--;
  setNum(health);
  if(bin::styleBlocks()){
      setStyleSheet("background:rgba(187, 51, 0,"+QString::number(health*0.1+0.1)+");border:"+QString::number(health)+"px solid #555;");
  }
  else
      setStyleSheet("background:rgba(255,"+QString::number(health*20)+",0,230);border:4px solid #666;");
  }
}

void block::update(){
    shooter* par=((shooter*)parent());
    move(x(),y()-5);
    if(this->y()<45&& this->x()> -300){
        par->blockSignals(true);
        if(par->ui->actionProgress->isEnabled())par->on_actionProgress_triggered();
        if(QMessageBox::question(par,"Lose","GAME OVER",QMessageBox::Retry,QMessageBox::Ok)
           ==QMessageBox::Retry){
          par->blockSignals(false);
          par->on_actionNew_Game_triggered();
      }
      exit(0);
    }
  }
