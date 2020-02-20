#ifndef BULLET_H
#define BULLET_H
#include <QThread>
#include <QLabel>
#include "block.h"
#include "shooter.h"

class bullet : public QLabel
{
    shooter* all;
public:
    bullet(shooter* stage):QLabel((QWidget*)stage){
        all=stage;
        //moveToThread(this);
        run();
    }

    void run(){
        resize(6,20);
        show();
        setStyleSheet("background:yellow");
        block** blocks= all->kirpich;
        for(short i=40;i<620;i+=5){
            move(all->ui->tank->x()+14,i);
            all->repaint();
            for(short k=0;k<all->BLOCKS;k++){
              if(blocks[k]->y()==i &&
                 blocks[k]->x()    <x() &&
                 blocks[k]->x()+100>x()){
                    blocks[k]->hit();i=620;break;
              }
            }
        }
        if(all->rushed>=all->BLOCKS){
            QMessageBox::information(all,"You won!",
                 "You already broke all\n"+QString::number(all->BLOCKS)+" BLOCKS!!!");
            bin::set(bin::brokenBlocks(), bin::mazesComplete()+1);
            all->on_actionNew_Game_triggered();
        }
    }
    ~bullet(){}
};

#endif // BULLET_H
