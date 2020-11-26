#ifndef LABERINTO_H
#define LABERINTO_H
#include <QGraphicsItem>
#include<QPainter>

class laberinto: public QGraphicsItem
{
    int w,h;
    int posx, posy;


public:
    laberinto(int w_,int h_, int x, int y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // LABERINTO_H
