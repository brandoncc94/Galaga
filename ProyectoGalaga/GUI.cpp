#define tam 24
//Prueba
//Hola
#include "mainwindow.h"
#include "threads.h"
#include <stdio.h>
#include <stdlib.h>
#include <QMovie>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDesktopWidget>

static MainWindow *window = NULL;
static Ui::MainWindow *ui = NULL;
QMovie *enemiesAnimations[tam];
QLabel *enemiesLabels[tam];

void centerScreen(int pWidth, int pHeight){
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    int x = (screenWidth - pWidth) / 2;
    int y = (screenHeight - pHeight) / 2;

    window->resize(pWidth, pHeight);
    window->move(x, y);
}

void loadBGImage(){
    //Background Image
    QPalette palette;
    palette.setBrush(window->backgroundRole(), QBrush(QImage("../images/BGSpace.jpg")));
    window->setPalette(palette);
}

void loadGalagaTitle(){
    QMovie *galagaTitle = new QMovie("../images/galaga.gif");
    ui->lblGalaga->setMovie(galagaTitle);
    galagaTitle->start();
}

void loadShip(){
    QMovie *shipMovie = new QMovie("../images/ship.png");
    ui->lblShip->setMovie(shipMovie);
    shipMovie->start();
}

void loadEnemies(){
    //Inicializar el arreglo
    QWidget *parent = new QWidget();
    //parent->resize(400, 400);
    int x = 1, y = 0, corte = 0;
    for(int i = 0; i < tam; i++){
        //Create the label container
        QLabel *label = new QLabel(parent);
        enemiesLabels[i] = label;
        //Create the martian
        QMovie *martian = new QMovie("../images/martian.png");
        enemiesAnimations[i] = martian;

        //Asiggn to the label its respective martian
        enemiesLabels[i]->setMovie(enemiesAnimations[i]);

        //Make the martian visible
        enemiesAnimations[i]->start();
        enemiesAnimations[i]->stop();

        enemiesLabels[i]->move(x * corte, y);

        if(i>11){
            corte = i - 11;
            y=60;

        }else{
            corte = i + 1;
            x = 40;
        }

        printf("%d, ", enemiesLabels[i]->y());

        //Let's locate the martians
        enemiesLabels[i]->setAlignment(Qt::AlignCenter);
    }
    ui->martiansContainer->addWidget(parent);
}

void expandAliens(){
    QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();
    int x[5] = {100, 200, 300, 400, 250};
    int y[5] = {100, 100, 100, 100, 250};
    int martian[5] = {0, 5, 8, 12, 18};
    for(int i = 0; i < 5; i++){
        QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[martian[i]], "geometry");
        path->setDuration(500);
        path->setStartValue(QRect(enemiesLabels[martian[i]]->x(),enemiesLabels[martian[i]]->y(),32,32));
        path->setEndValue(QRect(x[i],y[i],32,32));
        path->start();
    }
    martiansAnimations->start();
}

void organizeAliens(){
    //Delete the countdown gif
    delete ui->lblCountdown;
    QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();

    //resize window
    centerScreen(800, 600);

    //Organize martians
    int width = 32;
    int height = 32;
    int differenceX = 150;
    int differenceY = 150;
    for(int i = 0; i < tam; i++){
        QPropertyAnimation *path1 = new QPropertyAnimation(enemiesLabels[i], "geometry");
        QPropertyAnimation *path2 = new QPropertyAnimation(enemiesLabels[i], "geometry");
        path1->setDuration(300);
        path2->setDuration(300);

        int posX = enemiesLabels[i]->x();
        int posY = enemiesLabels[i]->y();

        path1->setStartValue(QRect(posX, posY, width, height));
        path1->setEndValue(QRect(posX, posY + height, width, height));

        path2->setStartValue(QRect(posX, posY + height, width, height));
        path2->setEndValue(QRect(differenceX, differenceY, width, height));

        martiansAnimations->addAnimation(path1);
        martiansAnimations->addAnimation(path2);
        if(i > 3 && i < 7)
            differenceX = 250;
        else if(i > 7 && i < 11)
            differenceX = 350;
        else if(i>11 && i< 17){
            differenceX = 200;
            differenceY = 200;
        }else if(i>17)
            differenceX = 300;
    }
    martiansAnimations->start();
}

void recoverAliens(){
    int posX[tam] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440};
    int posY = 0;
    QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();

    for(int i = 0; i < tam; i++){
        QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[i], "geometry");
        path->setDuration(500);
        path->setStartValue(QRect(enemiesLabels[i]->x(),enemiesLabels[i]->y(),32,32));
        path->setEndValue(QRect(posX[i],posY,32,32));
        path->start();
        if(i >= 12)
            posY = 60;
    }
    martiansAnimations->start();
}

void counterDown(){
    QMovie *countdown = new QMovie("../images/countdown.gif");
    ui->lblCountdown->setMovie(countdown);
    countdown->start();
}

void MainWindow::ejecutarAnimacion(int pAnimation){
    //Hilo del Cajero
    switch(pAnimation){
        case 0:
            counterDown();
            hiloAnimacion->tiempo = 15000;
            break;
        case 1:
            loadBGImage();
            organizeAliens();
            hiloAnimacion->tiempo = 2000;
            break;
        case 2:
            loadGalagaTitle();
            expandAliens();
            hiloAnimacion->tiempo = 2000;
            break;
        case 3:
            delete ui->lblGalaga;
            recoverAliens();
            break;
    }
}

void loadGUI(MainWindow *pWindow, Ui::MainWindow *pUi){
    window = pWindow;
    ui = pUi;
    centerScreen(500, 281);
    loadShip();
    loadEnemies();
}


