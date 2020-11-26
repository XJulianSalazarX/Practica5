#ifndef MONEDAS_H
#define MONEDAS_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Monedas : public QObject, public QGraphicsItem
{
    Q_OBJECT
    float posx,posy;
    float ancho,alto;
    float filas,columnas;
    QTimer *timer;
    QPixmap *pixmap;
public:
    Monedas(float posx_, float posy_);

    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);


    float getPosx() const;
    float getPosy() const;

signals:
public slots:
    void Actualizacion();
};

#endif // MONEDAS_H
