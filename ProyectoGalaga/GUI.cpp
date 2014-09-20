#define tam 24

#include "mainwindow.h"
#include "threads.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <QMovie>
#include <QMutex>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QDebug>
#include <QPolygon>
#include <QMessageBox>
#include <QCoreApplication>


static MainWindow *window = (MainWindow*)malloc(sizeof(MainWindow));
static Ui::MainWindow *ui = NULL;
QMovie *enemiesAnimations[tam];
QLabel *enemiesLabels[tam];
int totalShots = 0;
int posX[tam] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440};
int yAdvance = 0, readyToEliminate = 0, distance = 100;
int createTimeThread = 1, movingAsideTime = 4000, canSum = 1;
int resetHighscore = 0, isBonus = 0, reanudarAtaque = 1;
int isGameover = 0;
/*Definimos el rango de puntos por enemigos destruído*/
int pointsPerEnemie[5] = {10, 15, 25, 30, 40};

QString userName;

int getTipo(int pId);
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
     ui->lblShip->setScaledContents(true);
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
        QMovie *martian;
        if(i <= 4)
            martian = new QMovie("../images/redBossMartian.png");
        else if(i <= 8)
            martian = new QMovie("../images/greenMartian.png");
        else if(i<=12)
            martian =  new QMovie("../images/blueMartian.png");
        else if(i<=16)
            martian =  new QMovie("../images/purpleMartian.png");
        else if(i<=20)
            martian =  new QMovie("../images/greenMartian.png");
        else
            martian =  new QMovie("../images/redMartian.png");

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
    QParallelAnimationGroup *martiansAnimations = new QParallelAnimationGroup();
    int x[5] = {100, 200, 300, 400, 250};
    int y[5] = {100, 100, 100, 100, 250};
    int martian[5] = {0, 5, 8, 12, 18};
    for(int i = 0; i < 5; i++){
        QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[martian[i]], "geometry");
        path->setDuration(500);
        path->setStartValue(QRect(enemiesLabels[martian[i]]->x(),enemiesLabels[martian[i]]->y(),32,32));
        path->setEndValue(QRect(x[i],y[i],32,32));
        martiansAnimations->addAnimation(path);
    }
    martiansAnimations->start();
}

void distributeAliens(enemy_t *pTmp){
    QParallelAnimationGroup *martiansAnimations = new QParallelAnimationGroup();
    int x = 400;
    int y = 650;
    while(pTmp != NULL){
        if(!pTmp->isFilled){
            QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[pTmp->id], "geometry");
            path->setDuration(900);
            path->setStartValue(QRect(enemiesLabels[pTmp->id]->x(),enemiesLabels[pTmp->id]->y(),32,32));
            path->setEndValue(QRect(enemiesLabels[pTmp->id]->x() - x,enemiesLabels[pTmp->id]->y() + y,32,32));
            martiansAnimations->addAnimation(path);
        }
        x-= 50;
        pTmp = pTmp->next;
    }
    martiansAnimations->start();
}

void moveAliensSides(int pShiftX, enemy_t *pTmp, int pDuracion){
    int x = 0, y = 0;
    yAdvance+= 2;
    while(pTmp != NULL){
        if(pTmp->isFilled==1){
            if(window->enemiesManagerThread->enemies[pTmp->id]==2){
                qDebug("move");
                pTmp = pTmp->next;
                continue;
            }
            x = enemiesLabels[pTmp->id]->x();
            y = enemiesLabels[pTmp->id]->y();

            QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[pTmp->id], "geometry");
            path->setDuration(pDuracion);

            path->setStartValue(QRect(x,y,32,32));
            if(x == 0)
                x - pShiftX;

            path->setEndValue(QRect(x + pShiftX,y + 2,32,32));
            path->start();
        }
        pTmp = pTmp->next;
    }
}

void organizeAliens(){
    //Delete the countdown gif
    delete ui->lblCountdown;
    QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();

    //resize window1
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
    int posY = 0;
    QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();

    for(int i = 0; i < tam; i++){
        QPropertyAnimation *path = new QPropertyAnimation(enemiesLabels[i], "geometry");
        path->setDuration(500);
        path->setStartValue(QRect(enemiesLabels[i]->x(),enemiesLabels[i]->y(),32,32));
        path->setEndValue(QRect(posX[i],posY,32,32));
        path->start();
        if(i > 11)
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

    enemiesManagerThread = new EnemiesManager(this);
    connect(enemiesManagerThread,SIGNAL(enemiesManagerRequest(int)),this, SLOT(executeEnemiesManager(int))); //Cuando este thread sea ejecutado...
    enemiesManagerThread->start();
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
            if(!isBonus){
                delete ui->lblGalaga;
                recoverAliens();
            }
            ui->lblShip->move(340,440);
            ui->lblShip->show();
            if(!createTimeThread)
                animationThread->time = 100;
            else
                animationThread->time = 1000;
            break;
        case 4:
            //Resetear enemigos
            for(int i = 0; i < tam; i++)
                updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, -1, -1, 0, 0);

            //Enemigos iniciales
            if(!isBonus){
                for(int i = 5; i < 9; i++){
                    updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, 1, 1, 1, pointsPerEnemie[0]);
                    enemiesManagerThread->enemies[i]=1;
                }

                for(int i = 17; i < 21; i++){
                    updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, 1, 1, 1, pointsPerEnemie[0]);
                    enemiesManagerThread->enemies[i]=1;
                }
            }else{
                int tipo = -1;
                int vidas = 1;

                for(int i = 0; i < tam; i++){
                    tipo = getTipo(i);
                    if(tipo == 5)
                        vidas = 2;
                    updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, vidas, tipo, 1, pointsPerEnemie[tipo - 1]);
                    enemiesManagerThread->enemies[i] = 1;
                }
            }

            if(createTimeThread)
                distributeAliens(enemiesManagerThread->enemiesList->firstNode->next);
            else{
                enemy *tmp = enemiesManagerThread->enemiesList->firstNode->next;
                while(tmp != NULL){
                    if(tmp->isFilled){
                        enemiesLabels[tmp->id]->show();
                    }
                    else
                        enemiesLabels[tmp->id]->hide();
                    tmp = tmp->next;
                }

                ui->lblShip->move(340,440);
                for(int i = 0; i < tam; i++){
                    enemiesLabels[i]->setMovie(enemiesAnimations[i]);
                    enemiesLabels[i]->move(posX[i], (i <= 12) ? 0 : 60);
                }
            }

            animationThread->time = 50;
            break;
        case 5:
            ui->topFrame->setVisible(1);
            ui->topFrame->setStyleSheet("background-image: url('../images/header.png'); border: none;");

            animationThread->time = movingAsideTime;

            trickThread = new TrickThread(this);
            connect(trickThread,SIGNAL(trickRequest(int, int)),this, SLOT(executeTrick(int, int))); //Cuando este thread sea ejecutado...
            trickThread->start();

            if(reanudarAtaque){
                //Hilo de Control de Ataque
                enemiesAttackThread = new EnemiesAttack(this);
                connect(enemiesAttackThread,SIGNAL(enemiesAttackRequest()),this,SLOT(executeAttack()));
                enemiesAttackThread->stop=0;
                enemiesAttackThread->start();
                reanudarAtaque = 0;
            }

            if(createTimeThread){ //Solo la primera vez
                timeThread = new TimeThread(this);
                connect(timeThread,SIGNAL(timeRequest(int)),this, SLOT(executeTime(int))); //Cuando este thread sea ejecutado...
                timeThread->game->player->name = ui->lblPlayerName->text().toLocal8Bit().data();
                userName = QString(timeThread->game->player->name);
                timeThread->start();
                isGameover=1;

            }else{
                if(ui->lcdLevel->value() <= 5){
                    movingAsideTime -= 500;
                    animationThread->time = movingAsideTime;
                    trickThread->time = movingAsideTime;
                    timeThread->value = 0;
                    ui->lcdTime->display(timeThread->value);
                    canSum = 1;
                }
            }
            running=1;
            break;
        case 6:
            moveAliensSides(distance, enemiesManagerThread->enemiesList->firstNode->next, animationThread->time);
            break;
        case 7:
            moveAliensSides(-distance,enemiesManagerThread->enemiesList->firstNode->next, animationThread->time);
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

    lblBullet->setGeometry(QRect(x-95, y-60, 16, 16)); //pruebelo no ... aca debería de salir arribita de la nave

    path->setStartValue(QRect(x - 95, y - 60, 16, 16));//inicio de la animacion
    path->setEndValue(QRect(x - 95, 10, 16, 16)); //fin

    path->start();  //iniciar animación
    lblBullet->movie()->start();
}


void checkCollide(QLabel*);
bool check(QLabel*,QLabel*,int,int);

void MainWindow::executeBullet(QLabel *lblBullet, int pUpdateShots){
    if(pUpdateShots)
        totalShots--;
    else{
        moveBullet(lblBullet);
    }
}

void MainWindow::checkCollideAttack(collideEnemyThread * enemy){
    if(enemy->animation==1){
        enemy->stop = 1;
        enemiesLabels[enemy->enemy]->hide();
        timeThread->game->player->lifes--;
        ui->lblShip->hide();
        QThread::msleep(200);
        ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
        ui->lblShip->setScaledContents(true);
        ui->lblShip->show();
        running=1;
        qDebug("Fin animacion ataque");
    }
    if(check(enemiesLabels[enemy->enemy],ui->lblShip,95,45)){
        qDebug("Kamikaze exitoso");
        enemy->animation=1;
        enemy->time=400;
        QMutex m;
        m.lock();
        updateEnemies(enemiesManagerThread->enemiesList->firstNode, enemy->enemy, -1, -1, 0, 0);
        enemiesManagerThread->enemies[enemy->enemy]=0;
        enemiesLabels[enemy->enemy]->setMovie(new QMovie("../images/shipExplosionB.gif"));
        enemiesLabels[enemy->enemy]->movie()->start();
        enemiesLabels[enemy->enemy]->setScaledContents(true);
        ui->lblShip->setMovie(new QMovie("../images/shipExplosionPlayer.gif"));
        ui->lblShip->movie()->start();
        ui->lblShip->setScaledContents(true);
        m.unlock();
        running=0;
    }
}

void MainWindow::checkCollideBullet(collideBulletThread * collideThread, int pAnimation){
    if(pAnimation >-1){
        collideThread->stop=1;
        timeThread->game->player->lifes--;
        ui->lblShip->hide();
        running=0;
        QThread::msleep(200);
        ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
        ui->lblShip->setScaledContents(true);
        ui->lblShip->show();
        running=1;
    }else{
        if(check(collideThread->lblBullet,ui->lblShip,95,45)){
            collideThread->animation = 1;
            collideThread->time =400;
            //collideThread->msleep(45);
            ui->lblShip->setMovie(new QMovie("../images/shipExplosionPlayer.gif"));
            ui->lblShip->movie()->start();
            ui->lblShip->setScaledContents(true);
            timeThread->game->player->lifes--;
            qDebug("PEGO EL AZUL");
            collideThread->lblBullet->hide();
            qDebug()<<"COLLIDE";

            running=0;
        }
    }
}


void MainWindow::checkCollide(collideBulletThread * collideThread, int pAnimation){
    if(pAnimation >-1){
        if(enemiesManagerThread->enemies[pAnimation]==0){
            enemiesLabels[collideThread->animation]->hide();
        }
        collideThread->stop = 1;
    }else{
        for(int i = 0; i < tam; i++){
            if(enemiesManagerThread->enemies[i]==0)
                continue;
            if(check(collideThread->lblBullet,enemiesLabels[i],0,0)){
                qDebug("Choque");
                if(collideThread->lblBullet->isHidden()){
                    qDebug("Ingrese");
                    break;
                }
                collideThread->animation = i;
                collideThread->time =400;
                int tipo = findTypeOfEnemy(enemiesManagerThread->enemiesList->firstNode, i);
                if(tipo==5){
                    if(findLifesOfEnemy(enemiesManagerThread->enemiesList->firstNode,i)>1){
                        updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, 1, 5, 1, pointsPerEnemie[4]);
                        enemiesLabels[i]->setPixmap(QPixmap("../images/orangeBossMartian.png",0,Qt::AutoColor));
                        enemiesLabels[i]->setScaledContents(true);
                        timeThread->game->player->score += pointsPerEnemie[tipo - 1];
                        if(resetHighscore){
                            ui->lcdHighscore->display(0);
                            resetHighscore = 0;
                        }
                        if(tipo != -1)
                            ui->lcdHighscore->display( ui->lcdHighscore->value() + pointsPerEnemie[tipo - 1]);
                        collideThread->lblBullet->hide();
                        qDebug()<<"COLLIDE QUITA VIDA";
                        break;
                    }
                }

                QMutex m;
                m.lock();
                updateEnemies(enemiesManagerThread->enemiesList->firstNode, i, -1, -1, 0, 0);
                enemiesManagerThread->enemies[i]=0;
                m.unlock();
                //collideThread->msleep(45);

                enemiesLabels[i]->setMovie(new QMovie("../images/shipExplosion.gif"));
                enemiesLabels[i]->movie()->start();
                enemiesLabels[i]->setScaledContents(true);
                timeThread->game->player->score += pointsPerEnemie[tipo - 1];
                if(resetHighscore){
                    ui->lcdHighscore->display(0);
                    resetHighscore = 0;
                }
                ui->lcdHighscore->display( ui->lcdHighscore->value() + pointsPerEnemie[tipo - 1]);
                collideThread->lblBullet->hide();
                qDebug()<<"COLLIDE";
                break;
            }
        }
    }
}


bool check(QLabel * lblBullet,QLabel * lblEnemy,int x,int y){
    return (lblBullet->pos().x()+x < lblEnemy->pos().x() + lblEnemy->width())
            && (lblBullet->pos().y()+y < lblEnemy->pos().y() + lblEnemy->height()) &&
            (lblBullet->pos().x()+x + lblBullet->width() > lblEnemy->pos().x()) &&
            (lblBullet->pos().y()+y + lblBullet->height() > lblEnemy->pos().y());
}


//Time
void MainWindow::executeTime(int pValue){
    ui->lcdLevel->display(timeThread->game->nivel);
    if(timeThread->game->nivel != -1){
        if(!isBonus){
            if(timeThread->isRunning){
                if(canSum)
                    ui->lcdTime->display(pValue);
                checkIfWinLevel();
            }
        }else{
            qDebug() << "SÍ 1";
            if(timeThread->isRunning){
                //QThread::msleep(10);
                qDebug() << "SÍ 2";
                if(ui->lcdTime->value() >= 45){
                    canSum = 0;
                    int killedEnemies = 0;
                    enemy *tmp = enemiesManagerThread->enemiesList->firstNode;
                    while(tmp != NULL){
                        if(!tmp->isFilled)
                           killedEnemies++;
                        tmp = tmp->next;
                    }
                    qDebug() << "SÍ 3";
                    killedEnemies-=1;
                    if(killedEnemies >= tam){
                        qDebug() << "SÍ 4";
                        ui->lcdHighscore->display(10000);
                        isBonus = 0;
                        reanudarAtaque = 1;
                        stopThreads();
                    }
                    else{
                        qDebug() << "SÍ 5";
                        ui->lcdHighscore->display(killedEnemies * 100);
                        isBonus = 0;
                        reanudarAtaque = 1;
                        stopThreads();
                    }
                }else{
                    if(canSum)
                        ui->lcdTime->display(ui->lcdTime->value() + 1);
                }
                //QThread::msleep(40);
            }
        }
    }
}

void MainWindow::stopThreads(){
    trickThread->stop = 1;
    readyToEliminate = 0;
    timeThread->isRunning = 0;
    canSum = 0;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Galaga");
    timeThread->game->player->score += ui->lcdHighscore->value() * ui->lcdTime->value();
    QString message = "¡Nivel Completado! \n Reporte: \n   Usuario: " +  userName +
            "\n   Vidas: "+ QString::number(timeThread->game->player->lifes) + " \n   Puntaje: "
            + QString::number(ui->lcdHighscore->value()) + "\n   Tiempo: " + QString::number(ui->lcdTime->value())  +
            "\n   Total: " + QString::number(timeThread->game->player->score) + "\n\n¿listo para el siguiente nivel?";
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);

    while(msgBox.exec() != QMessageBox::Yes){}

    createTimeThread = 0;
    yAdvance = 0;
    ui->lcdHighscore->display(0);
    ui->lcdTime->display(0);
    resetHighscore = 1;
    timeThread->game->nivel++;
    animationThread->time = 10;

     //Bonus
    if(timeThread->game->nivel % 3 == 0){
        isBonus = 1;
        ui->lblNivel->setText("Bonus:");
        enemiesAttackThread->stop = 1;
    }else{
        isBonus = 0;
        ui->lblNivel->setText("Nivel:");
        reanudarAtaque = 0;
    }
    timeThread->isRunning = 1;
    animationThread->animation = 3;
}

void MainWindow::checkIfWinLevel(){
    int hasWin = 1;
    enemy *tmp = enemiesManagerThread->enemiesList->firstNode;
    while(tmp != NULL){
        if(tmp->isFilled)
            hasWin = 0;
        tmp = tmp->next;
    }

    if(hasWin && readyToEliminate){
        stopThreads();
    }
}



void MainWindow::ManagerThreadTime(ManagerThread* m_thread){
    if(m_thread->thread->stop)return;
    m_thread->thread->stop;

    int tipo = 0, vidas = 1;
    if(m_thread->thread->enemy <= 4){
        tipo = 5;
        vidas = 2;
    }
    else if(m_thread->thread->enemy <= 8)
        tipo = 1;
    else if(m_thread->thread->enemy<=12)
        tipo = 2;
    else if(m_thread->thread->enemy<=16)
        tipo = 4;
    else if(m_thread->thread->enemy<=20)
        tipo = 1;
    else
        tipo = 3;

    updateEnemies(enemiesManagerThread->enemiesList->firstNode, m_thread->thread->enemy, vidas, tipo, 1, pointsPerEnemie[tipo-1]);
    enemiesManagerThread->enemies[m_thread->thread->enemy] = 1;
}


bool abductedShip(int boss){
    if(((enemiesLabels[boss]->x()+95-50)<=ui->lblShip->x() && ui->lblShip->x()<=(enemiesLabels[boss]->x()+95+50))){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::bossAttack(BossGalagaAttack* b){
    ui->lblOndas->show();
    switch (b->step) {
    case 1:

        if(abductedShip(b->bossGalaga)){
            b->abducted=1;
        }else
            b->abducted=0;

        break;

    case 2:
        if(b->abducted){
            if(enemiesManagerThread->enemies[b->bossGalaga]==0)break;
            enemiesAttackThread->stop = 1;
            timeThread->game->player->lifes--;

            running=0;
            QPropertyAnimation *animation = new QPropertyAnimation(ui->lblShip, "geometry",this);
            animation->setDuration(2000);
            animation->setStartValue(QRect(ui->lblShip->x(),ui->lblShip->y(),ui->lblShip->width(),ui->lblShip->height()));
            animation->setEndValue(QRect(enemiesLabels[b->bossGalaga]->x()+105,ui->lblShip->y()-80,ui->lblShip->width(),ui->lblShip->height()));
            animation->start();
        }

        break;

        case 3:
    {
            ui->lblOndas->hide();
            ui->lblShip->hide();
            QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[b->bossGalaga], "geometry",this);
            animation->setDuration(1000);

            int xShip=ui->lblShip->x()-95;
            int yShip=ui->lblShip->y()-40;

            int posY = (b->bossGalaga <= 12) ? 0 : 60;
            int x = posX[b->bossGalaga];

            animation->setStartValue(QRect(xShip,yShip,32,32));
            animation->setEndValue(QRect(x,posY + yAdvance + 2,32,32));
            animation->start();
            updateEnemies(enemiesManagerThread->enemiesList->firstNode, b->bossGalaga, 1, 5, 1, pointsPerEnemie[4]);
            enemiesManagerThread->enemies[b->bossGalaga]=1;
    }
        break;
    case 4:
        ui->lblShip->move(340,440);
        ui->lblShip->show();
        enemiesAttackThread = new EnemiesAttack(this);
        connect(enemiesAttackThread,SIGNAL(enemiesAttackRequest()),this,SLOT(executeAttack()));
        enemiesAttackThread->start();
        running=1;
    break;
    default:
        ui->lblOndas->hide();
        QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[b->bossGalaga], "geometry",this);
        animation->setDuration(1000);

        int xShip=enemiesLabels[b->bossGalaga]->x();
        int yShip=enemiesLabels[b->bossGalaga]->y();

        int posY = (b->bossGalaga <= 12) ? 0 : 60;
        int x = posX[b->bossGalaga];

        animation->setStartValue(QRect(xShip,yShip,32,32));
        animation->setEndValue(QRect(x,posY + yAdvance + 2,32,32));
        animation->start();

        break;
    }

}

//Fly Enemie
void MainWindow::executeAttack(){
    int random;
    int i=10;
    int tipo = -1;
    while(i>0){
        random=trickThread->randomize(0,23);
        if(enemiesManagerThread->enemies[random]==1){
            //qDebug(QString::number(random).toLocal8Bit().data());
            tipo = findTypeOfEnemy(enemiesManagerThread->enemiesList->firstNode, random);
            break;
        }
        i--;
    }

    if(tipo==4){
        tipo= trickThread->randomize(2,3);
    }

    switch(tipo){
        case 1:{
            this->AttackKamikaze(random);
        break;
        }
        case 2:{
            this->AttackBullet(random);

        break;
        }
        case 3:{
            this->AttackFlying(random);

        break;
        }
        case 5:{
            this->AttackBossGalaga(random);
        break;
        }
        default:
            qDebug() << "Ningún marciano seleccionado.";
        break;
    }
}

void MainWindow::AttackKamikaze(int random){
    if(enemiesManagerThread->enemies[random]!=0){
        updateEnemies(enemiesManagerThread->enemiesList->firstNode, random, 1, 1, 2, pointsPerEnemie[0]);
        enemiesManagerThread->enemies[random]=2;
        collideEnemyThread * collideEnemy_t = new collideEnemyThread(this);
        collideEnemy_t->enemy=random;
        QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[random], "geometry",this);
        QPropertyAnimation *animation2 = new QPropertyAnimation(enemiesLabels[random], "geometry",this);

        animation->setDuration(1500);
        animation2->setDuration(1000);

        animation->setEasingCurve(QEasingCurve::Linear);
        int xEnemy=enemiesLabels[random]->x();
        int yEnemy=enemiesLabels[random]->y();
        int xShip=ui->lblShip->x()-95;
        int yShip=ui->lblShip->y()-40;

        int posY = (random <= 12) ? 0 : 60;
        int x = posX[random];

        animation->setStartValue(QRect(xEnemy,yEnemy,32,32));
        animation->setEndValue(QRect(xShip,yShip,32,32));
        animation2->setStartValue(QRect(xShip,yShip,32,32));
        animation2->setEndValue(QRect(x,posY + yAdvance + 2,32,32));

        int lado=1;
        if(trickThread->randomize(1,100)>50)lado*=-1;
        QPainterPath path;
        path.moveTo(xEnemy,yEnemy);
        path.quadTo(xEnemy+200*lado,yEnemy+100,xShip,yShip);

        //setting value for animation on different position using QPainterPath
        for( double i = 0 ; i < 1; i = i+0.1) {
            animation->setKeyValueAt(i,QRect(path.pointAtPercent(i).toPoint(),QSize(30,30)));
        }
        QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();
        martiansAnimations->addAnimation(animation);
        martiansAnimations->addAnimation(animation2);
        connect(collideEnemy_t,SIGNAL(collideEnemyRequest(collideEnemyThread*)),this,SLOT(checkCollideAttack(collideEnemyThread*)));
        collideEnemy_t->start();
        martiansAnimations->start();
        enemiesLabels[random]->move(xShip,yShip);
        ManagerThread * manageAttack = new ManagerThread();
        manageAttack->thread=collideEnemy_t;
        manageAttack->enemy=random;
        manageAttack->time=2500;
        connect(manageAttack,SIGNAL(ManagerTRequest(ManagerThread*)),this,SLOT(ManagerThreadTime(ManagerThread*)));
        manageAttack->start();

    }
}

void MainWindow::AttackBullet(int random){
    qDebug()  << "Tipo 2 -> ";
    int randomX =trickThread->randomize(0,23);

    QLabel *lblBullet = new QLabel();
    lblBullet->setMovie(new QMovie("../images/bullet.gif"));
    lblBullet->setFixedHeight(16);
    lblBullet->setFixedWidth(16);

    QPropertyAnimation *path = new QPropertyAnimation(lblBullet, "geometry");

    path->setDuration(1500);
    int x = enemiesLabels[random]->x();
    int y = enemiesLabels[random]->y();

    ui->martiansContainer->addWidget(lblBullet);

    lblBullet->setGeometry(QRect(x+16, y+16, 16, 16));

    path->setStartValue(QRect(x + 16, y + 16, 16, 16));//inicio de la animacion
    //path->setEndValue(QRect(randomX, 700, 16, 16)); //fin
    path->setEndValue(QRect(ui->lblShip->x() - 95, ui->lblShip->y() - 45, 16, 16)); //fin

    path->start();  //iniciar animación
    lblBullet->movie()->start();

    BulletThread * bullet_T = new BulletThread(this);
    bullet_T->bullet->lblBullet=lblBullet;
    bullet_T->animation = 0;
    bullet_T->bullet->collideBullet = (void*) new collideBulletThread(this);
    collideBulletThread* c =(collideBulletThread*)bullet_T->bullet->collideBullet;
    c->lblBullet=bullet_T->bullet->lblBullet;
    connect(bullet_T,SIGNAL(bulletRequest(QLabel *, int)),this, SLOT(executeBullet(QLabel *, int))); //Cuando este thread sea ejecutado...
    connect(c,SIGNAL(collideBulletRequest(collideBulletThread*, int)),this,
            SLOT(checkCollideBullet(collideBulletThread*, int)));
    c->start();
    bullet_T->start();
}

void MainWindow::AttackFlying(int random){
    if(enemiesManagerThread->enemies[random]!=0){
        updateEnemies(enemiesManagerThread->enemiesList->firstNode, random, 1, 3, 2, pointsPerEnemie[2]);
        enemiesManagerThread->enemies[random]=2;
        collideEnemyThread * collideEnemy_t = new collideEnemyThread(this);
        collideEnemy_t->enemy=random;
        QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[random], "geometry",this);
        QPropertyAnimation *animation2 = new QPropertyAnimation(enemiesLabels[random], "geometry",this);

        animation->setDuration(1500);
        animation2->setDuration(1000);

        animation->setEasingCurve(QEasingCurve::Linear);
        int xEnemy=enemiesLabels[random]->x();
        int yEnemy=enemiesLabels[random]->y();
        int xShip=ui->lblShip->x()-95;
        int yShip=ui->lblShip->y()-40;

        int posY = (random <= 12) ? 0 : 60;
        int x = posX[random];

        int lado=1;
        if(trickThread->randomize(1,100)>50)lado*=-1;

        animation->setStartValue(QRect(xEnemy,yEnemy,32,32));
        animation->setEndValue(QRect(xShip,yShip,32,32));


        animation2->setStartValue(QRect(xShip,yShip,32,32));
        animation2->setEndValue(QRect(x,posY + yAdvance + 2,32,32));

        QPainterPath path;
        path.moveTo(xEnemy,yEnemy);
        path.quadTo(xEnemy+200*lado,yEnemy+100,xShip+100*lado,yShip+120);
        path.quadTo(xShip+125*lado,yShip-50,xShip+150*lado,yShip+30);
        path.quadTo(xShip+65*lado,yShip-70,xShip,yShip);

        //setting value for animation on different position using QPainterPath
        for( double i = 0 ; i < 1; i = i+0.1) {
            animation->setKeyValueAt(i,QRect(path.pointAtPercent(i).toPoint(),QSize(30,30)));
        }
        QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();
        martiansAnimations->addAnimation(animation);
        martiansAnimations->addAnimation(animation2);


        connect(collideEnemy_t,SIGNAL(collideEnemyRequest(collideEnemyThread*)),this,SLOT(checkCollideAttack(collideEnemyThread*)));
        collideEnemy_t->start();
        martiansAnimations->start();
        enemiesLabels[random]->move(xShip,yShip);
        ManagerThread * manageAttack = new ManagerThread();
        manageAttack->thread=collideEnemy_t;
        manageAttack->enemy=random;
        manageAttack->time=2500;
        connect(manageAttack,SIGNAL(ManagerTRequest(ManagerThread*)),this,SLOT(ManagerThreadTime(ManagerThread*)));
        manageAttack->start();

    }
}

void MainWindow::AttackBossGalaga(int random){
    qDebug()  << "Tipo 5 -> ";
    if(enemiesManagerThread->enemies[random]!=0){
        //CAMBIAR VIDAS
        updateEnemies(enemiesManagerThread->enemiesList->firstNode, random,2, 5, 2, pointsPerEnemie[0]);
        enemiesManagerThread->enemies[random]=2;
        QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[random], "geometry",this);
        animation->setDuration(1500);

        animation->setEasingCurve(QEasingCurve::Linear);
        int xEnemy=enemiesLabels[random]->x();
        int yEnemy=enemiesLabels[random]->y();

        animation->setStartValue(QRect(xEnemy,yEnemy,32,32));
        animation->setEndValue(QRect(245,280,32,32));

        int lado=1;
        if(trickThread->randomize(1,100)>50)lado*=-1;
        QPainterPath path;
        path.moveTo(xEnemy,yEnemy);
        path.quadTo(xEnemy+200*lado,yEnemy+100,245,280);

        //setting value for animation on different position using QPainterPath
        for( double i = 0 ; i < 1; i = i+0.1) {
            animation->setKeyValueAt(i,QRect(path.pointAtPercent(i).toPoint(),QSize(30,30)));
        }

        BossGalagaAttack* bossGAttack= new BossGalagaAttack();
        bossGAttack->bossGalaga=random;
        connect(bossGAttack,SIGNAL(bossGalagaAttackRequest(BossGalagaAttack*)),this
                ,SLOT(bossAttack(BossGalagaAttack*)));

        QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();
        martiansAnimations->addAnimation(animation);
        martiansAnimations->start();
        enemiesLabels[random]->move(245,300);
        bossGAttack->start();
    }
}



//Trick

QPolygon getPolygon(int pFigura){
    QPolygon polygon;
    qDebug()<< "Seleccionar poligono";
    switch(pFigura){
        case 0:
            //Estrella
            polygon << QPoint(250,110) << QPoint(190,298)
                    << QPoint(340,178) << QPoint(160,178)
                    << QPoint(310,298) << QPoint(260,110);
            break;
        case 1:
            //Triangulo
            polygon << QPoint(250,110) << QPoint(350,250)
                    << QPoint(150,250) << QPoint(260,110);
            break;
        case 2:
            //Cuadrado
            polygon << QPoint(250,110) << QPoint(350,110)
                    << QPoint(350,240) << QPoint(250,240)
                    << QPoint(260, 110);
            break;
        case 3:
            //Rombo
            polygon << QPoint(250,110) << QPoint(300,180)
                    << QPoint(250,250) << QPoint(200,180)
                    << QPoint(260, 110);
            break;
    }
    return polygon;
}

void MainWindow::executeTrick(int pId, int pRandom){
    switch (pId) {
        case 0:{
            pRandom = findEnemy(enemiesManagerThread->enemiesList->firstNode, pRandom);

            if(pRandom!=-1){
                enemiesLabels[pRandom]->show();
                QSequentialAnimationGroup *martiansAnimations = new QSequentialAnimationGroup();

                if(pRandom <= 4){
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/redBossMartian.png"));
                    trickThread->tipo = 5;
                    trickThread->vidas = 2;
                }
                else if(pRandom <= 8){
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/greenMartian.png"));
                    trickThread->tipo = 1;
                }
                else if(pRandom<=12){
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/blueMartian.png"));
                    trickThread->tipo = 2;
                }
                else if(pRandom<=16){
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/purpleMartian.png"));
                    trickThread->tipo = 4;
                }
                else if(pRandom<=20){
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/greenMartian.png"));
                    trickThread->tipo = 1;
                }
                else{
                    enemiesLabels[pRandom]->setMovie(new QMovie("../images/redMartian.png"));
                    trickThread->tipo = 3;
                }
                //updateEnemies(enemiesManagerThread->enemiesList->firstNode, pRandom, trickThread->vidas, trickThread->tipo, 2, pointsPerEnemie[trickThread->tipo -1]);

                enemiesLabels[pRandom]->movie()->start();
                QPropertyAnimation *animation = new QPropertyAnimation(enemiesLabels[pRandom], "geometry");
                QPropertyAnimation *animation2 = new QPropertyAnimation(enemiesLabels[pRandom], "geometry");
                QPropertyAnimation *animation3 = new QPropertyAnimation(enemiesLabels[pRandom], "geometry");

                animation->setDuration(trickThread->time * 0.20);
                animation2->setDuration(trickThread->time * 0.60);
                animation3->setDuration(trickThread->time * 0.20);

                //animation2->setEasingCurve(QEasingCurve::Linear);

                animation->setStartValue(QRect(-100,110,32,32));
                animation->setEndValue(QRect(250,110,32,32));

                QPainterPath path;

                QPolygon polygon = getPolygon(trickThread->randomize(0, 3));
                path.addPolygon(polygon);

                //setting value for animation on different position using QPainterPath
                for( double i = 0 ; i < 1; i = i+0.1) {
                    animation2->setKeyValueAt(i,QRect(path.pointAtPercent(i).toPoint(),QSize(32,32)));
                }

                int x = posX[pRandom];
                int posY = (pRandom <= 12) ? 0 : 60;

                animation3->setStartValue(QRect(260,110,32,32));
                animation3->setEndValue(QRect(x,posY + yAdvance + 2,32,32));

                martiansAnimations->addAnimation(animation);
                martiansAnimations->addAnimation(animation2);
                martiansAnimations->addAnimation(animation3);
                martiansAnimations->start();
                readyToEliminate = 0;
            }else
                readyToEliminate = 1;
            break;
        }
        case 1:
            pRandom = findEnemy(enemiesManagerThread->enemiesList->firstNode, pRandom);
            if(pRandom!=-1){
                enemiesLabels[pRandom]->show();
                updateEnemies(enemiesManagerThread->enemiesList->firstNode, pRandom, trickThread->vidas,trickThread->tipo,1, pointsPerEnemie[trickThread->tipo -1]);
                enemiesManagerThread->enemies[pRandom]=1;
            }

            readyToEliminate = 1;
            break;
    }
}

void MainWindow::executeEnemiesManager(int pId){
    switch(pId){
        case 0:
            //Initialize the list
            enemiesManagerThread->enemiesList = initialize(enemiesManagerThread->enemiesList);
            break;
        case 1:
            //Insertar enemigos
            for(int i = 0; i < tam; i++)
                insert(enemiesManagerThread->enemiesList->firstNode, i, 1, -1, 0, 0);
            break;
        case 2:
            //Listening changes
            if(isGameover && timeThread->game->player->lifes == 0){
                ui->lblGameOver->show();
                running=0;
                ui->lblShip->hide();
                enemiesManagerThread->id = 3;
            }
            break;
        case 3:
            QThread::msleep(3000);
            QCoreApplication::quit();
        break;
    }
}

void loadGUI(MainWindow *pWindow, Ui::MainWindow *pUi){
    window = pWindow;
    ui = pUi;
    centerScreen(500, 281);
    window->startThreads();
}

void MainWindow::load(Menu * pMenu){
    this->ui->lblPlayerName->setText(pMenu->nombre);
    loadGUI(this,this->ui);
}

int getTipo(int pId){
    if(pId <= 4)
        return 5;
    else if(pId <= 8)
        return 1;
    else if(pId<=12)
        return 2;
    else if(pId<=16)
        return 4;
    else if(pId<=20)
        return 1;
    else
        return 3;
}

//Handling keys behavior
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(running==0)return;
    //Control boundaries
    if(ui->lblShip->y() >= 430)
        ui->lblShip->move(ui->lblShip->x(),430);
    else if(ui->lblShip->y() <= 400)
        ui->lblShip->move(ui->lblShip->x(),400);
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
                bulletThread->bullet->collideBullet = (void*) new collideBulletThread(this);
                collideBulletThread* c =(collideBulletThread*)bulletThread->bullet->collideBullet;
                c->lblBullet=bulletThread->bullet->lblBullet;
                connect(bulletThread,SIGNAL(bulletRequest(QLabel *, int)),this, SLOT(executeBullet(QLabel *, int))); //Cuando este thread sea ejecutado...
                connect(c,SIGNAL(collideBulletRequest(collideBulletThread*, int)),this,
                        SLOT(checkCollide(collideBulletThread *, int)));
                c->start();
                bulletThread->start();

            }
            event->accept();
            break;
        case Qt::Key_Up:
            ui->lblShip->setPixmap(QPixmap("../images/fastShip.png", 0, Qt::AutoColor));
            //ui->lblShip->setFixedHeight(154);
            ui->lblShip->setScaledContents(true);
            ui->lblShip->move(QPoint(x, y-10));
            event->accept();
            break;
        case Qt::Key_Down:
            ui->lblShip->move(QPoint(x, y+10));
            ui->lblShip->setScaledContents(true);
            event->accept();
            break;
        case Qt::Key_Left:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipLeft.png", 0, Qt::AutoColor));
            ui->lblShip->setScaledContents(true);
            ui->lblShip->move(QPoint(x-10, y));
            event->accept();
            break;
        case Qt::Key_Right:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipRight.png", 0, Qt::AutoColor));
            //ui->lblShip->setFixedHeight(122);
            //ui->lblShip->setFixedWidth(66);
            ui->lblShip->setScaledContents(true);
            ui->lblShip->move(QPoint(x+10, y));
            event->accept();
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
    ui->lblShip->setScaledContents(true);
}
