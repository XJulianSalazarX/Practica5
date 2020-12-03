#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>

class Health: public QGraphicsTextItem
{
public:
    Health(QGraphicsItem *parent = 0);
    void decrease();
    int getHealth() const;
    void setHealth(int value);

private:
    int health;
};

#endif // HEALTH_H
