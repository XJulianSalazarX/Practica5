#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    scene1();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pacman;
    for(Monedas *i : coins)
        delete i;
    coins.clear();
    delete score;
    delete health;
    for(Enemy *i : ghosts)
        delete i;
    ghosts.clear();
    for(laberinto *i : paredes)
        delete i;
    paredes.clear();
    delete timerG;
    delete timerM;
    delete timerPac;
    delete timer;
    delete sound;
    delete soundDead;
    delete soundVictory;
}

void MainWindow::scene1()
{
    //escena
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->closeButton->setVisible(false);
    ui->pushButton->setVisible(false);

    this->setGeometry(700,100,770,912);
    this->setMinimumSize(width(),height());
    this->setMaximumSize(width(),height());
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QPixmap(":/imagenes/inicio.png").scaled(width()-20,height()-30));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(width()-20,height()-30);
    ui->graphicsView->setSceneRect(0,0,width()-20,height()-30);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->playButton->setGeometry(250,500,277,107);

    //personajes
    //pacman
    pacman = new Personajes();

    //laberinto
    crearLaberinto();

    //fantasmas
    CrearFantasmas();

    //puntaje
    score = new Score();

    //salud
    health = new Health();

    //sonido
    sound = new QMediaPlayer();
    sound->setMedia(QUrl("qrc:/musica/kart-mario.mp3"));
    soundDead = new QMediaPlayer();
    soundDead->setMedia(QUrl("qrc:/musica/pacman-dead.mp3"));
    soundVictory = new QMediaPlayer();
    soundVictory->setMedia(QUrl("qrc:/musica/victory.mp3"));

    //Qtimers
    timerM = new QTimer();
    timerG = new QTimer();
    timerPac = new QTimer();
    timer = new QTimer();
}

void MainWindow::scene2()
{
    //escena
    this->setGeometry(700,100,770,912);
    scene->setBackgroundBrush(QPixmap(":/imagenes/fondo_prueba.png"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(width()-20,height()-30);
    ui->graphicsView->setSceneRect(0,0,width()-20,height()-30);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if(!gameCreated){
        //pacman
        scene->addItem(pacman);
        pacman->setPos(pacman->getPosx(),pacman->getPosy());
        //laberinto
        agregarLaberinto();
        //monedas
        ConstruirMonedas();
        //puntaje
        scene->addItem(score);
        //salud
        scene->addItem(health);
        health->setY(score->y()+25);
        //fantasmas
        for(Enemy *i : ghosts){
            scene->addItem(i);
        }
    }
    else{
        pacman->setPos(pacman->getPosx(),pacman->getPosy());
        health->setY(health->y()+25);
        for(Enemy *i : ghosts)
            i->setPos(i->getPosx(),i->getPosy());
    }
    //monedas
    ConstruirMonedas();
    //sonido
    sound->play();
    //timers
    connect(timerPac,SIGNAL(timeout()),this,SLOT(ChocarFantasma()));
    connect(timerPac,SIGNAL(timeout()),this,SLOT(move()));
    timerPac->start(40);

    connect(timerG,SIGNAL(timeout()),this,SLOT(moveRedGhost()));
    connect(timerG,SIGNAL(timeout()),this,SLOT(moveOrangeGhost()));
    connect(timerG,SIGNAL(timeout()),this,SLOT(moveBlueGhost()));
    connect(timerG,SIGNAL(timeout()),this,SLOT(movePinkGhost()));
    timerG->start(50);

    connect(timer,SIGNAL(timeout()),this,SLOT(startTimerG()));

    connect(timerM,SIGNAL(timeout()),this,SLOT(Music()));
    timerM->start(30000);
}

void MainWindow::scene3()
{
    //desconectar y parar Qtimers
    sound->stop();
    timerM->stop();
    disconnect(timerM,SIGNAL(timeout()),this,SLOT(Music()));

    timerPac->stop();
    disconnect(timerPac,SIGNAL(timeout()),this,SLOT(move()));
    disconnect(timerPac,SIGNAL(timeout()),this,SLOT(ChocarFantasma()));

    timerG->stop();
    disconnect(timerG,SIGNAL(timeout()),this,SLOT(moveRedGhost()));
    disconnect(timerG,SIGNAL(timeout()),this,SLOT(moveOrangeGhost()));
    disconnect(timerG,SIGNAL(timeout()),this,SLOT(moveBlueGhost()));
    disconnect(timerG,SIGNAL(timeout()),this,SLOT(movePinkGhost()));

    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(startTimerG()));

    //quitar elementos de scena
    health->setVisible(false);
    score->setVisible(false);
    pacman->setVisible(false);
    for(Enemy *i : ghosts)
        i->setVisible(false);
    for(laberinto *i : paredes)
        i->setVisible(false);
    if(!coins.isEmpty()){
        for(Monedas *i : coins){
            scene->removeItem(i);
            delete i;
        }
        coins.clear();
    }

    //scena
    scene->setBackgroundBrush(QPixmap(":/imagenes/end.png"));
    ui->label->setVisible(true);
    ui->label->setGeometry(150,0,500,400);
    ui->label_2->setVisible(true);
    ui->label_2->setText(QString::number(score->getScore()));
    ui->label_2->setGeometry(300,250,400,200);
    ui->pushButton->setVisible(true);
    ui->pushButton->setGeometry(100,600,250,100);
    ui->closeButton->setVisible(true);
    ui->closeButton->setGeometry(400,600,250,100);

}

void MainWindow::on_playButton_clicked()
{
    ui->playButton->setVisible(false);
    scene2();
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_A) key = "A";
    else if(evento->key() == Qt::Key_D) key = "D";
    else if(evento->key() == Qt::Key_W) key = "W";
    else if(evento->key() == Qt::Key_S) key = "S";
}

void MainWindow::move()
{
    if(key == "A" && pacman->x()>=20){
        pacman->setRotation(180);
        pacman->Left();
        if(Chocar()) pacman->Right();
        ComerMonedas();
    }
    if(key == "D" && pacman->x()<=730){
        pacman->setRotation(0);
        pacman->Right();
        if(Chocar()) pacman->Left();
        ComerMonedas();
    }
    if(key == "W" && pacman->y()>=20){
        pacman->setRotation(270);
        pacman->Up();
        if(Chocar()) pacman->Down();
        ComerMonedas();
    }
    if(key == "S" && pacman->y()<=860){
        pacman->setRotation(90);
        pacman->Down();
        if(Chocar()) pacman->Up();
        ComerMonedas();
    }
}

void MainWindow::CrearFantasmas()
{
    ghosts.push_back(new Enemy(":/imagenes/red_ghost.png",20,245,2));
    ghosts.push_back(new Enemy(":/imagenes/pink_ghost.png",730,245,3));
    ghosts.push_back(new Enemy(":/imagenes/blue_ghost.png",20,600,3));
    ghosts.push_back(new Enemy(":/imagenes/orange_ghost.png",730,600,3));
}

void MainWindow::ChocarFantasma()
{
    for(Enemy *i : ghosts){
        if(pacman->collidesWithItem(i)){
            timerPac->stop();
            timerG->stop();
            timerM->stop();
            sound->stop();
            timer->start(2500);
            key = " ";
            health->decrease();
            pacman->DeadPacman();
            soundDead->play();
            if(health->getHealth()==0){
                scene3();
            }
        }
    }
}

void MainWindow::ConstruirMonedas()
{
    float posx=22,posy=23;
    for(int i=0;i<181;i++){
        coins.push_back(new Monedas(posx,posy));
        scene->addItem(coins[i]);
        coins[i]->setPos(coins[i]->getPosx(),coins[i]->getPosy());
        for(laberinto *pared : paredes){
            if(coins[i]->collidesWithItem(pared) or coins[i]->collidesWithItem(pacman)){
                scene->removeItem(coins[i]);
                delete coins[i];
                coins.removeAt(i);
                i--;
            }
        }
            posx += 44;
       if(posx>734){
           posx=22;
           if(posy<700) posy+=44;
           else posy+=47;
       }
    }
}

void MainWindow::ComerMonedas()
{
    int pos = 0;
    if(coins.size()==0){
        soundVictory->play();
        scene3();
    }
    for(Monedas *i : coins){
        if(pacman->collidesWithItem(i)){
            scene->removeItem(i);
            delete i;
            coins.removeAt(pos);
            score->increase();
            break;
        }
        pos ++;
    }
}

bool MainWindow::Chocar()
{
for(laberinto *i : paredes){
    if(pacman->collidesWithItem(i)) return true;
}
    return false;

}

bool MainWindow::ChoqueFantasmas(Enemy *enemy)
{
    for(laberinto *i : paredes){
        if(enemy->collidesWithItem(i)) return true;
    }
    return false;
}

void MainWindow::crearLaberinto()
{
    QString line;
    int pos;
    float width_,height_,posx,posy;
    QFile file(":/mapa/laberinto.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "No se puede abrir el archivo.";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        //ancho
        pos = line.indexOf(",");
        width_ = line.mid(0,pos).toFloat();
        line = line.mid(pos+1);
        //alto
        pos = line.indexOf(",");
        height_ = line.mid(0,pos).toFloat();
        line = line.mid(pos+1);
        //posx
        pos = line.indexOf(",");
        posx = line.mid(0,pos).toFloat();
        //posy
        posy = line.mid(pos+1).toFloat();
        paredes.push_back(new laberinto(width_,height_,posx,posy));
    }
    file.close();
}

void MainWindow::agregarLaberinto()
{
    for(laberinto *i : paredes)
        scene->addItem(i);
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::moveRedGhost()
{
    if(ghosts[0]->x() < pacman->x()){
        ghosts[0]->Right();
    }
    if(ghosts[0]->x() > pacman->x()){
        ghosts[0]->Left();
    }
    if(ghosts[0]->y() < pacman->y()){
        ghosts[0]->Down();
    }
    if(ghosts[0]->y() > pacman->y()){
        ghosts[0]->Up();
    }
}

void MainWindow::moveOrangeGhost()
{
    if(orangeMove == 0){
        ghosts[3]->Up();
        if(ChoqueFantasmas(ghosts[3]) or ghosts[3]->y()<=20){
            ghosts[3]->Down();
            orangeMove = rand()%4;
        }
    }
    else if(orangeMove == 1){
        ghosts[3]->Down();
        if(ChoqueFantasmas(ghosts[3])or ghosts[3]->y()>=860){
            ghosts[3]->Up();
            orangeMove = rand()%4;
        }
    }
    else if(orangeMove == 2){
        ghosts[3]->Right();
        if(ChoqueFantasmas(ghosts[3]) or ghosts[3]->x()>=730){
            ghosts[3]->Left();
            orangeMove = rand()%4;
        }
    }
    else if(orangeMove == 3){
        ghosts[3]->Left();
        if(ChoqueFantasmas(ghosts[3]) or ghosts[3]->x()<=20){
            ghosts[3]->Right();
            orangeMove = rand()%4;
        }
    }
}

void MainWindow::moveBlueGhost()
{
    if(blueMove == 0){
        ghosts[2]->Up();
        if(ChoqueFantasmas(ghosts[2]) or ghosts[2]->y()<=20){
            ghosts[2]->Down();
            blueMove = rand()%4;
        }
    }
    else if(blueMove == 1){
        ghosts[2]->Down();
        if(ChoqueFantasmas(ghosts[2])or ghosts[2]->y()>=860){
            ghosts[2]->Up();
            blueMove = rand()%4;
        }
    }
    else if(blueMove == 2){
        ghosts[2]->Right();
        if(ChoqueFantasmas(ghosts[2]) or ghosts[2]->x()>=730){
            ghosts[2]->Left();
            blueMove = rand()%4;
        }
    }
    else if(blueMove == 3){
        ghosts[2]->Left();
        if(ChoqueFantasmas(ghosts[2]) or ghosts[2]->x()<=20){
            ghosts[2]->Right();
            blueMove = rand()%4;
        }
    }
}

void MainWindow::movePinkGhost()
{
    if(ghosts[1]->x() < pacman->x()){
        ghosts[1]->Right();
        if(ChoqueFantasmas(ghosts[1])) ghosts[1]->Left();
    }
    else if(ghosts[1]->x() > pacman->x()){
        ghosts[1]->Left();
        if(ChoqueFantasmas(ghosts[1])) ghosts[1]->Right();
    }
    if(ghosts[1]->y() < pacman->y()){
        ghosts[1]->Down();
        if(ChoqueFantasmas(ghosts[1])) ghosts[1]->Up();
    }
     else if(ghosts[1]->y() > pacman->y()){
        ghosts[1]->Up();
        if(ChoqueFantasmas(ghosts[1])) ghosts[1]->Down();
    }
}

void MainWindow::Music()
{
    sound->play();
}

void MainWindow::startTimerG()
{
    timerPac->start(40);
    timerG->start(40);
    timerM->start(30000);
    sound->play();
    timer->stop();
}

void MainWindow::on_pushButton_clicked()
{
    gameCreated = true;
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->closeButton->setVisible(false);
    ui->pushButton->setVisible(false);
    //Poner elementos en la escena
    health->setVisible(true);
    score->setVisible(true);
    pacman->setVisible(true);
    for(Enemy *i : ghosts)
        i->setVisible(true);
    for(laberinto *i : paredes)
        i->setVisible(true);
    //reconstruir posiciones de juego
    //puntaje
    score->setScore(0);
    //salud
    health->setHealth(3);
    //pacman
    pacman->setPosx(370);
    pacman->setPosy(865);
    //fantasmas
    ghosts[0]->setPosx(20);
    ghosts[0]->setPosy(245);
    ghosts[1]->setPosx(730);
    ghosts[1]->setPosy(245);
    ghosts[2]->setPosx(20);
    ghosts[2]->setPosy(600);
    ghosts[3]->setPosx(730);
    ghosts[3]->setPosy(600);
    scene2();
}
