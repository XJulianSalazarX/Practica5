#include "laberinto.h"

laberinto::laberinto(int w_, int h_, int x, int y)
{
    posx = x;
    posy = y;
    setPixmap(QPixmap(":/imagenes/muro_opt.jpg").scaled(w_,h_));
}

int laberinto::getPosx() const
{
    return posx;
}

int laberinto::getPosy() const
{
    return posy;
}
