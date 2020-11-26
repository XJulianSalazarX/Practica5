#include "laberinto.h"

laberinto::laberinto(int w_,int h_, int x, int y)
{
   w = w_;
   h = h_;
   posx = x;
   posy = y;
}

QRectF laberinto::boundingRect() const
{
       return QRectF(-posx, -posy,w,h);
}

void laberinto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect((boundingRect()));
}
