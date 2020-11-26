#ifndef LABERINTO_H
#define LABERINTO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class laberinto: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int posx, posy;
public:
    laberinto(int w_,int h_, int x, int y);
    int getPosx() const;
    int getPosy() const;
};

#endif // LABERINTO_H
