#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "personajes.h"
#include "monedas.h"
#include "laberinto.h"
#include "score.h"
#include "enemy.h"
#include <QList>
#include <QMediaPlayer>
#include "health.h"
#include <QFile>
#include <QTextStream>

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
    void moveRedGhost();
    void moveOrangeGhost();
    void moveBlueGhost();
    void movePinkGhost();
    void move();
    void ChocarFantasma();
    void Music();
    void startTimerG();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    bool gameCreated = false;
    QString key;
    int orangeMove = 0;
    int blueMove = 1;
    Personajes *pacman;
    QList<Monedas *> coins;
    Score *score;
    Health *health;
    QList<Enemy *> ghosts;
    QList<laberinto *> paredes;
    QTimer *timerG;
    QTimer *timerM;
    QTimer *timerPac;
    QTimer *timer;

    //escenas
    void scene1();
    void scene2();
    void scene3();
    void scene4();

    //movimiento
    void keyPressEvent(QKeyEvent *evento);

    //paredes
    void crearLaberinto();
    void agregarLaberinto();
    bool Chocar();

    //monedas
    void ConstruirMonedas();
    void ComerMonedas();
    bool ComprobarMuro(float posx,float posy);

    //fantasmas
    void CrearFantasmas();
    bool ChoqueFantasmas(Enemy *enemy);

    //sonido
    QMediaPlayer *sound;
    QMediaPlayer *soundDead;
    QMediaPlayer *soundVictory;
};
#endif // MAINWINDOW_H
