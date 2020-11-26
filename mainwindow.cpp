#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //escena
    scene = new QGraphicsScene(0,0,748,880);
    scene->setBackgroundBrush(QPixmap(":/imagenes/fondo_blanco.jpg"));
    ui->graphicsView->setScene(scene);

    //pacman
    pacman = new Personajes();
    scene->addItem(pacman);
    pacman->setPos(pacman->getPosx(),pacman->getPosy());

    //laberinto
    ConstruirMuro();

    //monedas
    ConstruirMonedas();
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
        if(Chocar()) pacman->Right();
        ComerMonedas();

    }
    else if(evento->key() == Qt::Key_D && pacman->x()<=730){
        pacman->setRotation(0);
        pacman->Right();
        if(Chocar()) pacman->Left();
        ComerMonedas();
    }
    else if(evento->key() == Qt::Key_W && pacman->y()>=20){
        pacman->setRotation(270);
        pacman->Up();
        if(Chocar()) pacman->Down();
        ComerMonedas();
    }
    else if(evento->key() == Qt::Key_S && pacman->y()<=860){
        pacman->setRotation(90);
        pacman->Down();
        if(Chocar()) pacman->Up();
        ComerMonedas();
    }
}

void MainWindow::ConstruirMonedas()
{
    //total de monedas 160
    float posx=22,posy=30;
    Monedas *moneda;
    QList<Monedas>::iterator it;
    for(int i=0;i<181;){
       if(!ComprobarMuro(posx,posy)){
       moneda = new Monedas(posx,posy);
       coins.push_back(moneda);
       i++;
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
            delete i;
            coins.removeAt(pos);
            break;
        }
        pos ++;
    }
}

bool MainWindow::ComprobarMuro(float posx, float posy)
{
    if(posy ==30 or posy ==162 or posy==602 or posy==866){
       if(posx==378) return true;
    }
    else if(posy == 74 or posy == 118){
        if(posx==66.5 or posx==111 or posx==200 or posx==244.5 or posx==289 or posx==378
        or posx==467 or posx==511.5 or posx==556 or posx==645 or posx==689.5) return true;
    }
    else if(posy == 206){
        if(posx==66.5 or posx==111 or posx==200 or posx==289 or posx==333.5 or posx==378
        or posx==422.5 or posx==467 or posx==556 or posx==645 or posx==689.5) return true;
    }
    else if(posy == 250){
        if(posx==200 or posx==378 or posx==556) return true;
    }
    else if(posy == 294){
        if(posx==22 or posx==66.5 or posx==111 or posx==200 or posx==244.5 or posx==289
        or posx==378 or posx==467 or posx==511.5 or posx==556 or posx==645 or posx==689.5
        or posx==734)return true;
    }
    else if(posy == 338){
        if(posx==22 or posx==66.5 or posx==111 or posx==200 or posx==556 or posx==645
        or posx==689.5 or posx==734)return true;
    }
    else if(posy == 382 or posy == 470 or posy == 558){
        if(posx==22 or posx==66.5 or posx==111 or posx==200 or posx==289 or posx==333.5
        or posx==378 or posx==422.5 or posx==467 or posx==556 or posx==645 or posx==689.5
        or posx==734)return true;
    }
    else if(posy == 426){
        if(posx==22 or posx==66.5 or posx==111 or posx==289 or posx==333.5 or posx==378
        or posx==422.5 or posx==467 or posx==645 or posx==689.5 or posx==734) return true;
    }
    else if(posy == 514){
        if(posx==22 or posx==66.5 or posx==111 or posx==200 or posx==556 or posx==645
        or posx==689.5 or posx==734)return true;
    }
    else if(posy == 646){
        if(posx==66.5 or posx==111 or posx==200 or posx==244.5 or posx==289 or posx==378
        or posx==467 or posx==511.5 or posx==556 or posx==645 or posx==689.5)return true;
    }
    else if(posy == 690){
        if(posx==111 or posx==645) return true;
    }
    else if(posy == 734){
        if(posx==22 or posx==111 or posx==200  or posx==289 or posx==333.5 or posx==378
        or posx==422.5 or posx==467 or posx==556 or posx==645 or posx==734) return true;
    }
    else if(posy == 778){
        if( posx==200 or posx == 378  or posx==556) return true;
    }
    else if(posy == 822){
        if(posx==66.5 or posx==111 or posx==155.5 or posx==200 or posx==244.5 or posx==289
        or posx==378 or posx==467 or posx==511.5 or posx==556 or posx==600.5
        or posx==645 or posx==689.5)return true;
    }
    return false;
}

void MainWindow::ConstruirMuro()
{
    pared1=new laberinto(91,92,42,42); pared2=new laberinto(134,92,175,42);
    pared3=new laberinto(46,314,351,0); pared4=new laberinto(223,46,262,176);
    pared5=new laberinto(134,92,439,42); pared6=new laberinto(91,92,615,42);
    pared7=new laberinto(90,47,42,176); pared8=new laberinto(90,47,615,176);
    pared9=new laberinto(46,223,174,176); pared10=new laberinto(88,47,220,267);
    pared11=new laberinto(92,47,440,267); pared12=new laberinto(46,223,527,176);
    pared13=new laberinto(224,136,262,355); pared14=new laberinto(134,312,0,267);
    pared15=new laberinto(134,312,616,267); pared16=new laberinto(46,138,176,441);
    pared17=new laberinto(46,138,527,441); pared18=new laberinto(223,46,262,533);
    pared19=new laberinto(46,93,351,571); pared20=new laberinto(134,46,175,619);
    pared21=new laberinto(134,46,440,619); pared22=new laberinto(91,46,42,619);
    pared23=new laberinto(46,93,87,661); pared24=new laberinto(46,93,616,661);
    pared25=new laberinto(91,46,616,619); pared26=new laberinto(46,46,0,710);
    pared27=new laberinto(46,46,704,710); pared28=new laberinto(223,46,266,710);
    pared29=new laberinto(46,93,352,754); pared30=new laberinto(267,46,42,800);
    pared31=new laberinto(49,92,175,710); pared32=new laberinto(267,46,441,800);
    pared33=new laberinto(49,92,527,710);

    //gregar laberinto
    scene->addItem(pared1); scene->addItem(pared2); scene->addItem(pared3);
    scene->addItem(pared4); scene->addItem(pared5); scene->addItem(pared6);
    scene->addItem(pared7); scene->addItem(pared8); scene->addItem(pared9);
    scene->addItem(pared10); scene->addItem(pared11); scene->addItem(pared12);
    scene->addItem(pared13); scene->addItem(pared14); scene->addItem(pared15);
    scene->addItem(pared16); scene->addItem(pared17); scene->addItem(pared18);
    scene->addItem(pared19); scene->addItem(pared20); scene->addItem(pared21);
    scene->addItem(pared22); scene->addItem(pared23); scene->addItem(pared24);
    scene->addItem(pared25); scene->addItem(pared26); scene->addItem(pared27);
    scene->addItem(pared28); scene->addItem(pared29); scene->addItem(pared30);
    scene->addItem(pared31); scene->addItem(pared32); scene->addItem(pared33);

}

bool MainWindow::Chocar()
{
    if (pacman->collidesWithItem(pared1)or pacman->collidesWithItem(pared2)or pacman->collidesWithItem(pared3)or
    pacman->collidesWithItem(pared4)or pacman->collidesWithItem(pared5)or pacman->collidesWithItem(pared6)or
    pacman->collidesWithItem(pared7)or pacman->collidesWithItem(pared8)or pacman->collidesWithItem(pared9)or
    pacman->collidesWithItem(pared10)or pacman->collidesWithItem(pared11)or pacman->collidesWithItem(pared12)or
    pacman->collidesWithItem(pared13)or pacman->collidesWithItem(pared14)or pacman->collidesWithItem(pared15)or
    pacman->collidesWithItem(pared16)or pacman->collidesWithItem(pared17)or pacman->collidesWithItem(pared18)or
    pacman->collidesWithItem(pared19)or pacman->collidesWithItem(pared20)or pacman->collidesWithItem(pared21)or
    pacman->collidesWithItem(pared22)or pacman->collidesWithItem(pared23)or pacman->collidesWithItem(pared24)or
    pacman->collidesWithItem(pared25)or pacman->collidesWithItem(pared26)or pacman->collidesWithItem(pared27)or
    pacman->collidesWithItem(pared28)or pacman->collidesWithItem(pared29)or pacman->collidesWithItem(pared30)or
    pacman->collidesWithItem(pared31)or pacman->collidesWithItem(pared32)or pacman->collidesWithItem(pared33)) return true;

    return false;

}
