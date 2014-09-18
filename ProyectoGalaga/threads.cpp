#include "threads.h"    //Para manejar las funcions del thread
#include "struct.h"
#include <QtCore>       //Para el Mutex
#include <iostream>
#include <ctime>
#include "mainwindow.h"

//This is a reference to the functions below
AnimationThread::AnimationThread(QObject *parent):
    QThread(parent){}

//Develop what I want when the Threads is running
void AnimationThread::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            break;
        }

        mutex.unlock();

        emit animationRequest(this->animation);  //Execute the SIGNAL to make its SLOT

        this->msleep(this->time);
        if(this->animation == 7)
            this->animation--;
        else
            this->animation++;
    }
}


//This is a reference to the functions below
BulletThread::BulletThread(QObject *parent):
    QThread(parent){
    this->bullet->lblBullet=new QLabel();
}

//Develop what I want when the Threads is running
void BulletThread::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            this->quit();
            break;
        }
        this->msleep(100); //Time in miliseconds
        mutex.unlock();

        emit bulletRequest(this->bullet->lblBullet,0);  //Execute the SIGNAL to make its SLOT

        this->msleep(1500);

        emit bulletRequest(NULL, 1);  //Execute the SIGNAL to make its SLOT

        collideBulletThread * c = (collideBulletThread *)this->bullet->collideBullet;
        if(c->animation>-1){
            this->stop=1;
            delete this->bullet->lblBullet;
            break;
        }
        c->stop = 1;
        delete this->bullet->lblBullet;
        this->stop = 1;
    }
}

//This is a reference to the functions below
collideBulletThread::collideBulletThread(QObject *parent):
    QThread(parent){}

//Develop what I want when the Threads is running
void collideBulletThread::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100);
        if(this->stop!=0){
            this->quit();
            break;
        }
        this->msleep(100); //Time in miliseconds

        mutex.unlock();

        if(this->animation >-1){
            qDebug("Animacion");
            this->msleep(this->time);
        }

        emit collideBulletRequest(this, this->animation);  //Execute the SIGNAL to make its SLOT

    }
}


//This is a reference to the functions below
collideEnemyThread::collideEnemyThread(QObject *parent):
    QThread(parent){}

//Develop what I want when the Threads is running
void collideEnemyThread::run(){
    qDebug("ATAQUE");
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100);
        if(this->stop){
            this->quit();
            break;
        }
        this->msleep(100); //Time in miliseconds

        mutex.unlock();

        emit collideEnemyRequest(this);  //Execute the SIGNAL to make its SLOT
    }
}


//This is a reference to the functions below
TimeThread::TimeThread(QObject *parent):
    QThread(parent){
    this->game->nivel = 1;
    this->game->player->lifes = 3;
    this->game->player->score = 0;
}

//Develop what I want when the Threads is running
void TimeThread::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            break;
        }
        mutex.unlock();

        if(this->isRunning)
            this->value++;
        else
            this->value = 0;
        emit timeRequest(this->value);  //Execute the SIGNAL to make its SLOT
        this->msleep(this->time);
    }
}



//This is a reference to the functions below
ManagerThread::ManagerThread(QObject *parent):
    QThread(parent){

}

//Develop what I want when the Threads is running
void ManagerThread::run(){
    while(true){
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            break;
        }
        this->msleep(this->time);
        emit ManagerTRequest(this);  //Execute the SIGNAL to make its SLOT
        qDebug("STOOOOOOP");
        this->stop=1;
    }
}


//This is a reference to the functions below
TrickThread::TrickThread(QObject *parent):
    QThread(parent){}

//Develop what I want when the Threads is running
void TrickThread::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            break;
        }
        mutex.unlock();

        this->currentEnemie = this->randomize(0,23);
        this->msleep(this->time);
        if(this->stop)
            break;
        emit trickRequest(0, this->currentEnemie); //Execute the SIGNAL to make its SLOT

        this->msleep(this->time);
        emit trickRequest(1, this->currentEnemie);
    }
}

int TrickThread::randomize(int Min, int Max)
{
    qsrand(QTime::currentTime().msec());

    if (Min > Max)
    {
        int Temp = Min;
        Min = Max;
        Max = Temp;
    }
    qrand();
    return ((rand()%(Max-Min+1))+Min);
}


//This is a reference to the functions below
EnemiesManager::EnemiesManager(QObject *parent):
    QThread(parent){}

//Develop what I want when the Threads is running
void EnemiesManager::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            break;
        }
        mutex.unlock();

        emit enemiesManagerRequest(this->id); //Execute the SIGNAL to make its SLOT
        if(this->id < 2)
            this->id++;
        this->msleep(this->time);
    }
}


//This is a reference to the functions below
EnemiesAttack::EnemiesAttack(QObject *parent):
    QThread(parent){
}

//Develop what I want when the Threads is running
void EnemiesAttack::run(){
    qDebug("INICIADO EnemiesAttack");
    while(true){
        QMutex mutex;
        mutex.lock();
        this->msleep(100); //Time in miliseconds
        if(this->stop){
            qDebug("Finalizado");
            break;
        }
        mutex.unlock();
        qDebug("atacar");
        emit enemiesAttackRequest(); //Execute the SIGNAL to make its SLOT
        this->msleep(this->time);
    }
}
