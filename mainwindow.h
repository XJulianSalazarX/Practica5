#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRectF>
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>//recibir teclas
#include "personajes.h"
#include "monedas.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    float x,y;
    Personajes *pacman;
    Monedas *moneda;
    QList<Monedas *> coins;

    void keyPressEvent(QKeyEvent *evento);
    void ConstruirMonedas();
    void ComerMonedas();
    bool ComprobarMuro(float posx,float posy);
};
#endif // MAINWINDOW_H
