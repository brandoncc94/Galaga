#define tam 24

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
#include <QKeyEvent>

static MainWindow *window = NULL;
static Ui::MainWindow *ui = NULL;
QMovie *enemiesAnimations[tam];
QLabel *enemiesLabels[tam];
int totalShots = 0;

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
    ui->lblGalaga->setPixmap(QPixmap("../images/galaga.gif", 0, Qt::AutoColor));
}

void loadShip(){
     ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
}

void loadEnemies(){
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


void moveAliensSides(int pShiftX, int pShiftY){
    int x = 0, y = 0;
    for(int i = 0; i < tam; i++){
        x = enemiesLabels[i]->x();
        y = enemiesLabels[i]->y();
        if(y >= 400)
            y = 0;
        QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[i], "geometry");
        QPropertyAnimation *path2 = new QPropertyAnimation(enemiesLabels[i], "geometry");
        path->setDuration(1500);
        path2->setDuration(1500);

        path->setStartValue(QRect(x,y,32,32));
        path->setEndValue(QRect(x + pShiftX,y + pShiftY,32,32));

        path->start();
    }
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

void MainWindow::startThreads(){
    //Hilo Animación
    animationThread = new AnimationThread(this);
    connect(animationThread,SIGNAL(animationRequest(int)),this, SLOT(executeAnimation(int))); //Cuando este thread sea ejecutado...
    animationThread->start();
}

void MainWindow::executeAnimation(int pAnimation){
    //Hilo animacion
    switch(pAnimation){
        case 0:
            ui->lblShip->hide();
            ui->topFrame->setVisible(0);
            counterDown();
            loadShip();
            loadEnemies();
            animationThread->time = 15000;
            break;
        case 1:
            loadBGImage();
            organizeAliens();
            animationThread->time = 2000;
            break;
        case 2:
            loadGalagaTitle();
            expandAliens();
            animationThread->time = 2000;
            break;
        case 3:
            delete ui->lblGalaga;
            ui->topFrame->setVisible(1);
            ui->topFrame->setStyleSheet("background-image: url('../images/header.png'); border: none;");
            recoverAliens();
            ui->lblShip->move(340,440);
            ui->lblShip->show();
            animationThread->time = 10;
            break;
        case 4:
            timeThread = new TimeThread(this);
            connect(timeThread,SIGNAL(timeRequest(int)),this, SLOT(executeTime(int))); //Cuando este thread sea ejecutado...
            timeThread->start();
            animationThread->time = 3000;
            break;
        case 5:
            moveAliensSides(100, 10);
            break;
        case 6:
            moveAliensSides(-100, 10);
            break;
    }
}


//Bullet
void moveBullet(QLabel *lblBullet){
    QPropertyAnimation *path = new QPropertyAnimation(lblBullet, "geometry");
    path->setDuration(1500);
    int x = ui->lblShip->x();
    int y = ui->lblShip->y();

    lblBullet->setMovie(new QMovie("../images/bullet.gif"));
    lblBullet->setFixedHeight(16);
    lblBullet->setFixedWidth(16);// y el resto es la animación como siempre lo hago

    ui->martiansContainer->addWidget(lblBullet); //agregar el label para que se vea graficamente

    lblBullet->setGeometry(QRect(x-60, y-60, 16, 16)); //pruebelo no ... aca debería de salir arribita de la nave

    path->setStartValue(QRect(x - 60, y - 60, 16, 16));//inicio de la animacion
    path->setEndValue(QRect(x - 60, 0, 16, 16)); //fin

    path->start();  //iniciar animación
    lblBullet->movie()->start();
}

void MainWindow::executeBullet(QLabel *lblBullet, int pUpdateShots){
    if(pUpdateShots)
        totalShots--;
    else
        moveBullet(lblBullet);
}

//Time
void MainWindow::executeTime(int pValue){
    ui->lcdTime->display(pValue);
}

void loadGUI(MainWindow *pWindow, Ui::MainWindow *pUi){
    window = pWindow;
    ui = pUi;
    centerScreen(500, 281);
    window->startThreads();
}

//Handling keys behavior
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Control boundaries
    if(ui->lblShip->y() >= 430)
        ui->lblShip->move(ui->lblShip->x(),430);
    else if(ui->lblShip->y() <= 20)
        ui->lblShip->move(ui->lblShip->x(),430);
    if(ui->lblShip->x() >= 660)
        ui->lblShip->move(660,ui->lblShip->y());
    else if(ui->lblShip->x() <= 80)
        ui->lblShip->move(80,ui->lblShip->y());
    int x = ui->lblShip->x();
    int y = ui->lblShip->y();

    //Depending on the arrow pressed
    switch(event->key()){
        case Qt::Key_Space:
            if(totalShots <=4){
                totalShots++;
                bulletThread = new BulletThread(this);
                connect(bulletThread,SIGNAL(bulletRequest(QLabel *, int)),this, SLOT(executeBullet(QLabel *, int))); //Cuando este thread sea ejecutado...
                bulletThread->start();
            }
            event->accept();
            break;
        case Qt::Key_Up:
            ui->lblShip->setPixmap(QPixmap("../images/fastShip.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(154);
            ui->lblShip->move(QPoint(x, y-10));
            event->accept();
            break;
        case Qt::Key_Down:
            ui->lblShip->move(QPoint(x, y+10));
            event->accept();
            break;
        case Qt::Key_Left:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipLeft.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(122);
            ui->lblShip->setFixedWidth(66);
            ui->lblShip->move(QPoint(x-10, y));
            event->accept();
            break;
        case Qt::Key_Right:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipRight.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(122);
            ui->lblShip->setFixedWidth(66);
            ui->lblShip->move(QPoint(x+10, y));
            event->accept();
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
    ui->lblShip->setFixedHeight(122);
    ui->lblShip->setFixedWidth(100);
}
