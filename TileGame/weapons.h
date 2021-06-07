#ifndef WEAPONS_H
#define WEAPONS_H
#include "tile_types.h"
#include <QList>
#include <QPair>

class Weapon:public QObject, public QGraphicsRectItem{
    Q_OBJECT
    int listX;
    int durability=0;
    int durability_max=0;
public:
    QString png="";
    explicit Weapon(int x):listX(x)
    {
        this->setBrush(QBrush(QColor(100,100,100)));
        QPen pen = QPen(Qt::PenStyle::DashLine);
        pen.setColor(Qt::gray);
        this->setPen(pen);
        this->setFlag(QGraphicsItem::ItemIsSelectable);
        this->setRect(SIZE*listX*1.2+SIZE/5,SIZE*5.1,SIZE,SIZE);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override{
        QGraphicsRectItem::paint(painter,option,widget);
        {//drawing picture
            painter->drawPixmap(rect().x(),rect().y(),SIZE,SIZE,png);
        };
        {//drawing text
            QFont font = painter->font();
            font.setPixelSize(SIZE/5);
            painter->setFont(font);
            painter->setPen(Qt::green);
            if(durability_max!=0)
                painter->drawText(SIZE*listX*1.2+SIZE/5,SIZE*6.1,
                                  QString::number(durability)+"/"+QString::number(durability_max));
        }
    }
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override{
        event->accept();
        if(event->button()!=Qt::LeftButton)return;
        emit selected(listX);
    }
signals:
    void selected(int);
public:
    Weapon* setType(QPair<QString,int> type){
        png = type.first;
        durability_max = durability = type.second;
        return this;
    }
    int getDurabilty(){
        return durability;
    }
    int use(Tile* on_which){
        int damage = std::min<int>(durability,on_which->getHealth());
        on_which->damage(damage);
        durability-=damage;
        return durability;
    }
};

#endif // WEAPONS_H
