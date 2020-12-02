#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QDebug>

class Enemy: public QObject, public QGraphicsItem
{
    Q_OBJECT

    int posx,posy;
    int velocidad;
    float ancho,alto;
    float filas;
    QTimer *timer;
    QPixmap *pixmap;
    float begin;

public:
    Enemy(QString nombre,float posx_,float posy_);

    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void Up();
    void Down();
    void Left();
    void Right();

signals:
public slots:
    void Actualizacion();
};

#endif // ENEMY_H
