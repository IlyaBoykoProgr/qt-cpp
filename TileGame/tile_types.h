#ifndef TILE_TYPES_H
#define TILE_TYPES_H
//basic
#include <QString>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QDebug>
//paint engine
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
//std
#include <thread>

#define SIZE 50

enum Tile_types{
    empty, weapon, monster, coin
};

class Tile: public QObject, public QGraphicsRectItem{
    Q_OBJECT
    short listX, listY;
    float health=0,health_max=0;
    QString png = QString("");
public:
    Tile_types type;
    explicit Tile(int x, int y, QGraphicsRectItem* parent = nullptr, QObject* parent2 = nullptr):
            QObject(parent2),QGraphicsRectItem(parent),listX(x),listY(y)
    {
        this->setBrush(Qt::white);
        this->setPen(QPen(Qt::black,2));
        this->setFlag(QGraphicsItem::ItemIsSelectable);
        this->setRect(listX*SIZE,listY*SIZE,SIZE,SIZE);
        this->setTransformOriginPoint(this->rect().center());
        connect(this,&Tile::dies,this,&Tile::whenDies);
        connect(this,&Tile::touched,this,&Tile::proceedClick);
    }
    Tile* setType(QPair<QString,int> type, Tile_types tt){
        this->type = tt;
        png = type.first;
        health = health_max = type.second;
        return this;
    }
    QPair<QString,int> getType(){
        return {png,health_max};
    }
    ~Tile(){emit dies(nullptr);}
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override{
        event->accept();
        if(event->button()!=Qt::LeftButton)return;
        emit touched(this);
        scene()->clearSelection();
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override{
        QGraphicsRectItem::paint(painter,option,widget);
        {//drawing pixmap
            painter->drawPixmap(rect().x(),rect().y(),QPixmap(png));
        }
        if(health_max>0){//drawing text
            QFont font = painter->font();
            font.setPixelSize(SIZE/5);
            painter->setFont(font);
            painter->drawText(SIZE*listX,SIZE*(listY+1),
                              QString::number(health)+"/"+QString::number(health_max));
                        //drawing heart
            QPixmap img(":/pixmap/life.png");
            int w=SIZE/5;
            int x=listX*SIZE+SIZE-w;
            int y=listY*SIZE+SIZE-w;
            painter->drawPixmap(x,y,w,w,img);
        }
    }
public:
    float getHealth(){return health;}

    float damage(float value){
        health-=value;
        if(health<0){
            health=0;
            emit dies(this);
        }
        return health;
    }
signals:
    void touched(Tile*);
    void dies(Tile*);
public slots:
    void proceedClick(){
        switch(type){
        default:
        break;
        }
    }
    void whenDies(){}
};


#endif // TILE_TYPES_H
