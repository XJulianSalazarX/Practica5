#include "enemy.h"

Enemy::Enemy(QString nombre,float posx_,float posy_)
{
    timer = new QTimer();
    filas = 0;
    pixmap = new QPixmap(nombre);

    posx = posx_;
    posy = posy_;
    this->setPos(posx_,posy_);
    velocidad =3;

    begin = 0;

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
    begin = 216;
    filas = begin;
    posy -= velocidad;
    setPos(posx,posy);
}

void Enemy::Down()
{
    begin = 72;
    filas = begin;
    posy += velocidad;
    setPos(posx,posy);
}

void Enemy::Left()
{
    begin = 144;
    filas = begin;
    posx -= velocidad;
    setPos(posx,posy);
}

void Enemy::Right()
{
    begin = 0;
    filas = begin;
    posx += velocidad;
    setPos(posx,posy);
}

void Enemy::Actualizacion()
{
    filas += 36;
    if(filas >= 72+begin){
        filas = begin;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
