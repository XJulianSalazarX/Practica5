#include "personajes.h"

Personajes::Personajes(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;
    begin = 0;
    suma = 31.25;
    end = 125;
    pixmap = new QPixmap(":/imagenes/PACMAN (2).png");

    posy = 865;
    posx = 370;
    velocidad =5;

    //dimensiones de la imagen
     ancho = 31.25;
     alto = 28;
     timer->start(120);
     connect(timer,&QTimer::timeout,this,&Personajes::Actualizacion);

}

Personajes::Personajes(QString nombre, float ancho_, float alto_, int posx_, int posy_)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;
    begin = 0;
    suma = 24;
    end = 48;

    pixmap = new QPixmap(nombre);

    posx = posx_;
    posy = posy_;
    velocidad = 5;

    //dimensiones de la imagen
    ancho = ancho_;
    alto = alto_;
    timer->start(300);
    connect(timer,&QTimer::timeout,this,&Personajes::Actualizacion);

}
int Personajes::getPosx() const
{
    return posx;
}

void Personajes::setPosx(int value)
{
    posx = value;
}

int Personajes::getPosy() const
{
    return posy;
}

void Personajes::setPosy(int value)
{
    posy = value;
}

QRectF Personajes::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Personajes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);
}

void Personajes::Up()
{
    posy -= velocidad;
    setPos(posx,posy);
}

void Personajes::Down()
{
    posy += velocidad;
    setPos(posx,posy);
}

void Personajes::Left()
{
    posx -= velocidad;
    setPos(posx,posy);
}

void Personajes::Right()
{
    posx += velocidad;
    setPos(posx,posy);
}

void Personajes::Actualizacion()
{
    columnas += suma;
    if(columnas >= end){
        columnas = begin;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
