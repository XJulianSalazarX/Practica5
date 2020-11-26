#include "laberinto.h"

laberinto::laberinto(int w_, int h_, int x, int y)
{
    setPixmap(QPixmap(":/imagenes/muro_opt.jpg").scaled(w_,h_));
    this->setPos(x,y);
}
