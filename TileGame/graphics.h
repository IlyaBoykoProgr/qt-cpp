#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QBrush>
#include <QColor>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include "tile_types.h"
#include "weapons.h"

class Graphics : public QGraphicsView{
    Q_OBJECT
public:
    explicit Graphics(QWidget *parent = nullptr);

public slots:
    void collectCoins();
    void openCards();
    void tileClicked(Tile*);
    void weaponSelected(int s){selected_weapon=s;}
    void setRandomType(Tile* tile);
private:
    QGraphicsScene* scene;
    QList<Tile*> tiles;
    QPushButton *butt_collect, *butt_reveal;
    unsigned long coins = 0;

    Weapon* weapon[4];
    int selected_weapon=0;

    void resizeEvent(QResizeEvent*);
    bool gameOver();
    bool gameWin();
    QPair<QString,int> emptiness = {"",0};
    const QList<QPair<QString,int>> weapon_types ={
        {":/pixmap/weapon1.png",3}, // [0] - knife
        {":/pixmap/weapon2.png",10} // [1] - idk what is that
    };
    const QList<QPair<QString,int>> monster_types ={
        {":/pixmap/monster1.png",4}, // [0] - purple monster
        {":/pixmap/monster2.png",10},// [1] - blue monster
        {":/pixmap/monster3.png",5}, // [2] - green monster
        {":/pixmap/monster4.png",11},// [3] - yellow monster
        {":/pixmap/monster5.png",20},// [4] - orange moster
        {":/pixmap/monster6.png",7}, // [5] - red moster
    };
    const QPair<QString,int> coin_type = {
        ":/pixmap/coin.png",1
    };
public:
    ~Graphics(){
        delete scene;
        foreach(Tile* tile,tiles)delete tile;
        delete butt_collect;
        delete butt_reveal;
        for(short i=0;i<4;i++)delete weapon[i];
    }
};

#endif // GRAPHICS_H
