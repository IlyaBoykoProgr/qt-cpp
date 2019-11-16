#include "block.h"

block::block(int x, int y,short health,shooter* parent)
{
    setFont(QFont("Aerial",20));
    setAlignment(Qt::AlignCenter);
    setParent(parent);
    connect(parent,SIGNAL(pif_paf(int)),this,SLOT(update()));
    setGeometry(x+3,y,94,40);
    show();
    h=health+1;
    destroy();
}

void block::destroy(){
  if(h<1){
   move(-200,0);
   bin::set(bin::brokenBlocks()+1);
   ((shooter*)parent())->rushed++;
   emit achieve(bin::brokenBlocks());
  }else{
  h--;
  setNum(h);
  if(bin::styleBlocks())
      setStyleSheet("background:#B30;border:"+QString::number(9-h)+"px solid #555;");
  else
      setStyleSheet("background:rgba(255,"+QString::number(h*20)+",0,230);border:4px solid #666;");
  }
}

void block::update(){
    move(x(),y()-5);
    if(this->y()<45&& this->x()> -200){
        shooter* par=((shooter*)parent());
      if(QMessageBox::question(par,"Lose","GAME OVER",QMessageBox::Retry,QMessageBox::Ok)
           ==QMessageBox::Retry){
          par->on_actionNew_Game_triggered();
      }
      exit(0);
    }
  }
