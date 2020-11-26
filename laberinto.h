#ifndef LABERINTO_H
#define LABERINTO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class laberinto: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    laberinto(int w_,int h_, int x, int y);
};

#endif // LABERINTO_H
