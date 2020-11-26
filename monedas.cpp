#include "monedas.h"

Monedas::Monedas(float posx_, float posy_)
{
    timer = new QTimer();
    filas=0;
    columnas=0;
    pixmap = new QPixmap(":/imagenes/coin_gold.png");
    posx = posx_;
    posy = posy_;

    ancho = 32;
    alto = 32;
    timer->start(120);
    connect(timer,&QTimer::timeout,this,&Monedas::Actualizacion);
}

float Monedas::getPosx() const
{
    return posx;
}

float Monedas::getPosy() const
{
    return posy;
}

QRectF Monedas::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Monedas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = nullptr;
    widget = nullptr;
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);
}

void Monedas::Actualizacion()
{
    columnas += 32;
    if(columnas >= 256){
        columnas = 0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
