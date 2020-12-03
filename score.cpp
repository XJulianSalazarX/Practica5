#include "score.h"

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

void Score::increase()
{
    score+=10;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore() const
{
    return score;
}

void Score::setScore(int value)
{
    score = value;
    setPlainText(QString("Score: ") + QString::number(score));
}
