#include "graphics.h"

Graphics::Graphics(QWidget *parent) : QGraphicsView(parent)
{
   scene = new QGraphicsScene;
   this->setWindowTitle("Game");
   this->setScene(scene);

   scene->clear();
   scene->setBackgroundBrush(Qt::white);
   for(short i=0;i<25;i++){//Tiles creation
       tiles.append(new Tile(i%5,i/5));
       setRandomType(tiles[i]);
       connect(tiles[i],&Tile::touched,this,&Graphics::tileClicked);
       scene->addItem(tiles[i]);
   }
   for(short i=0;i<4;i++){//Weapons creation
       weapon[i]= new Weapon(i);
       connect(weapon[i],&Weapon::selected,this,&Graphics::weaponSelected);
       scene->addItem(weapon[i]);
   }
   {//services
       QFont font = QFont("Calibri",SIZE/6);

       butt_collect = new QPushButton("Collect coins\n5c per use");
       butt_collect->setGeometry(SIZE*5,0,SIZE,SIZE);
       butt_collect->setFont(font);
       butt_collect->show();
       scene->addWidget(butt_collect);
       connect(butt_collect,&QPushButton::clicked,this,&Graphics::collectCoins);

       butt_reveal = new QPushButton("Reveal blank cards\n10c per use");
       butt_reveal->setGeometry(SIZE*5,SIZE,SIZE,SIZE);
       butt_reveal->setFont(font);
       butt_reveal->show();
       scene->addWidget(butt_reveal);
       connect(butt_reveal,&QPushButton::clicked,this,&Graphics::openCards);
   }
   this->resize(scene->width(),scene->height());
   this->setWindowIcon(QIcon(":/pixmap/life.png"));
   this->show();
}

void Graphics::tileClicked(Tile* which = nullptr){
    Tile* clicked = (which==nullptr)?(Tile*)sender():which;
    if(clicked==nullptr)return;
    switch(clicked->type){
    case Tile_types::weapon:
        if(weapon[selected_weapon]->getDurabilty()!=0)return;
        weapon[selected_weapon]->setType(clicked->getType());
        clicked->setType(emptiness,empty);
    break;
    case Tile_types::monster:
        weapon[selected_weapon]->use(clicked);
        if(weapon[selected_weapon]->getDurabilty()==0)
            weapon[selected_weapon]->setType(emptiness);
        if(clicked->getHealth()==0)
            clicked->setType(coin_type,coin);
    break;
    case Tile_types::empty:
        setRandomType(clicked);
    break;
    case Tile_types::coin:
        coins++;
        setWindowTitle("Coins: "+QString::number(coins));
        clicked->setType(emptiness,empty);
    break;
    }
    if(gameOver()){
        QApplication::exit(
            QMessageBox::question(this,"GameOver!","You died of monster's attack.\nRestart?")==QMessageBox::Yes?
            -45:0
        );
    }
    if(gameWin()){
        QApplication::exit(
            QMessageBox::question(this,"You won!","You defeated them. How?..\nRestart?")==QMessageBox::Yes?
            -45:0
        );
    }
    scene->update();
}

void Graphics::setRandomType(Tile *tile){
    if(tile==nullptr)return;
    switch (rand()%2){
        case 0:
            tile->setType(weapon_types[
                rand()%weapon_types.length()
            ],Tile_types::weapon);
        break;
        case 1:
            tile->setType(monster_types[
                rand()%monster_types.length()
            ],Tile_types::monster);
        break;
        default:
            tile->setType(emptiness,empty);
        break;
    }//no coins!!!
}

bool Graphics::gameOver(){
    for(short i=0;i<25;i++)
        if(tiles[i]->type!=monster)
            return false;
    for(short i=0;i<4;i++)
        if(weapon[i]->getDurabilty()!=0)
            return false;
    return true;
}
bool Graphics::gameWin(){
    for(short i=0;i<25;i++)
        if(tiles[i]->type!=Tile_types::weapon)
            return false;
    for(short i=0;i<4;i++)
        if(weapon[i]->getDurabilty()==0)
            return false;
    return true;
}

void Graphics::collectCoins(){
    if(coins<5)return;
    foreach(Tile* i,tiles)
        if(i->type==coin)tileClicked(i);
    coins-=5;
    setWindowTitle("Coins: "+QString::number(coins));
}

void Graphics::openCards(){
    if(coins<10)return;
    foreach(Tile* i,tiles)
        if(i->type==empty)tileClicked(i);
    coins-=10;
    setWindowTitle("Coins: "+QString::number(coins));
}

void Graphics::resizeEvent(QResizeEvent *event){
    event->accept();
    this->fitInView(sceneRect());
    if(height()==0)showMinimized();
}
