#include "enemy.h"

Enemy::Enemy(QString nombre,float posx_,float posy_)
{
    timer = new QTimer();
    filas = 0;
    pixmap = new QPixmap(nombre);

    posy = posy_;
    posx = posx_;
    this->setPos(posx,posy);
    velocidad =3;

    //dimensiones de la imagen
     ancho = 30;
     alto = 36;
     timer->start(150);
     connect(timer,&QTimer::timeout,this,&Enemy::Actualizacion);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,0,filas,ancho,alto);
}

void Enemy::Up()
{
    posy -= velocidad;
    setPos(posx,posy);
}

void Enemy::Down()
{
    posy += velocidad;
    setPos(posx,posy);
}

void Enemy::Left()
{
    posx -= velocidad;
    setPos(posx,posy);
}

void Enemy::Right()
{
    posx += velocidad;
    setPos(posx,posy);
}

void Enemy::Actualizacion()
{
    filas += 36;
    if(filas >= 72){
        filas = 0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
