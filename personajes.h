#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QDebug>

class Personajes : public QObject, public QGraphicsItem
{
    Q_OBJECT

    int posx,posy;
    int velocidad;
    float ancho,alto;
    float filas,columnas;
    QTimer *timer;
    QPixmap *pixmap;
public:
    explicit Personajes(QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void Up();
    void Down();
    void Left();
    void Right();

    int getPosx() const;
    void setPosx(int value);
    int getPosy() const;
    void setPosy(int value);

signals:
public slots:
    void Actualizacion();

};

#endif // PERSONAJES_H
