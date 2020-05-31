#ifndef BULLET_H
#define BULLET_H
#include <QThread>
#include <QLabel>
#include "block.h"
#include "shooter.h"

class bullet : public QLabel
{
    shooter* game;
public:
    bullet(shooter* stage):QLabel((QWidget*)stage){
        game=stage;
        run();
    }

    void run(){
        resize(6,20);
        show();
        setStyleSheet("background:yellow");
        block** blocks= game->kirpich;
        for(short i=40;i<620;i+=5){
            move(game->ui->tank->x()+14,i);
            game->repaint();
            for(short k=0;k<game->BLOCKS;k++){
              if(blocks[k]->y()==i &&
                 blocks[k]->x()    <x() &&
                 blocks[k]->x()+100>x()){
                    blocks[k]->hit();i=620;break;
              }
            }
        }
        if(game->rushed>=game->BLOCKS){
            if(game->ui->actionProgress->isEnabled())game->on_actionProgress_triggered();
            QMessageBox::information(game,"You won!",
                 "You already broke all\n"+QString::number(game->BLOCKS)+" BLOCKS!!!");
            bin::set(bin::brokenBlocks(), bin::mazesComplete()+1);
            game->on_actionNew_Game_triggered();
        }
    }
    ~bullet(){}
};

#endif // BULLET_H
