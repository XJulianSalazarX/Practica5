#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRectF>
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>//recibir teclas
#include "personajes.h"
#include "monedas.h"
#include "laberinto.h"
#include "score.h"
#include "enemy.h"
#include <QList>
#include <QMediaPlayer>
#include "health.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playButton_clicked();
    void on_closeButton_clicked();
    void moveGhosts();
    void move();
    void ChocarFantasma();
    void Music();
    void startTimerG();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    QString key;
    Personajes *pacman;
    Monedas *moneda;
    QList<Monedas *> coins;
    laberinto *muro1;
    Score *score;
    Health *health;
    QList<Enemy *> ghosts;
    QTimer *timerG;
    QTimer *timerM;
    QTimer *timer;

    //escenas
    void scene1();
    void scene2();
    void scene3();
    void scene4();

    //movimiento
    void keyPressEvent(QKeyEvent *evento);

    //paredes
    void ConstruirMuro();
    bool Chocar();

    //monedas
    void ConstruirMonedas();
    void ComerMonedas();
    bool ComprobarMuro(float posx,float posy);

    //fantasmas
    void CrearFantasmas();
    //sonido
    QMediaPlayer *sound;

    laberinto *pared1, *pared2, *pared3, *pared4, *pared5, *pared6, *pared7, *pared8, *pared9,
    *pared10, *pared11, *pared12, *pared13, *pared14, *pared15, *pared16, *pared17, *pared18,
    *pared19, *pared20, *pared21, *pared22, *pared23, *pared24, *pared25, *pared26, *pared27,
    *pared28, *pared29,*pared30, *pared31, *pared32, *pared33;
};
#endif // MAINWINDOW_H
