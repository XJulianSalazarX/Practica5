#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //escena
    scene = new QGraphicsScene(0,0,748,880);
    scene->setBackgroundBrush(QPixmap(":/imagenes/mapa3.jpg"));
    ui->graphicsView->setScene(scene);

    //pacman
    pacman = new Personajes();
    scene->addItem(pacman);
    pacman->setPos(pacman->getPosx(),pacman->getPosy());

    //monedas
    moneda = new Monedas(25,30,0);
    scene->addItem(moneda);
    moneda->setPos(22,74);
    //ConstruirMonedas();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_A && pacman->x()>=20){
        pacman->setRotation(180);
        pacman->Left();
        ComerMonedas();

    }
    else if(evento->key() == Qt::Key_D && pacman->x()<=730){
        pacman->setRotation(0);
        pacman->Right();
        ComerMonedas();
    }
    else if(evento->key() == Qt::Key_W && pacman->y()>=20){
        pacman->setRotation(270);
        pacman->Up();
        ComerMonedas();
    }
    else if(evento->key() == Qt::Key_S && pacman->y()<=860){
        pacman->setRotation(90);
        pacman->Down();
        ComerMonedas();
    }
}

void MainWindow::ConstruirMonedas()
{
    //total de monedas 160
    float posx=22,posy=30;
    int pos = 0;
    Monedas *moneda;
    QList<Monedas>::iterator it;
    for(int i=0;i<160;i++,pos++){
       if(!ComprobarMuro(posx,posy)){
       moneda = new Monedas(posx,posy,pos);
       coins.push_back(moneda);
       }
       posx += 44.5;
       if(posx>734){
           posx=22;
           posy+=44;
       }
    }

    for(Monedas *i : coins){
        scene->addItem(i);
       i->setPos(i->getPosx(),i->getPosy());
    }
}

void MainWindow::ComerMonedas()
{
    int pos = 0;
    for(Monedas *i : coins){
        if(pacman->collidesWithItem(i)){
            scene->removeItem(i);
            coins.removeAt(pos);
            break;
        }
        pos ++;
    }
}

bool MainWindow::ComprobarMuro(float posx, float posy)
{
    if(posy == 30 or posy == 159){
       if(posx==378) return true;
    }
    else if(posy == 74 or posy == 118){
        if(posx==66.5 or posx==111 or posx==200 or posx==244.5 or posx==289 or posx==378
        or posx==467 or posx==511.5 or posx==556 or posx==645 or posx==689.5) return true;
    }
    else if(posy == 203){

    }
    else if(posy == 247){

    }
    else if(posy == 291){

    }
    else if(posy == 335){

    }
    else if(posy == 379){

    }
    else if(posy == 423){

    }
    else if(posy == 467){

    }
    else if(posy == 511){

    }
    else if(posy == 555){

    }
    else if(posy == 599){

    }
    else if(posy == 643){

    }
    else if(posy == 687){

    }
    return false;
}
