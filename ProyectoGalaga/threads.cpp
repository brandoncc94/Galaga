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
            break;
        }
        this->msleep(100); //Time in miliseconds
        mutex.unlock();

        emit bulletRequest(this->bullet->lblBullet, 0);  //Execute the SIGNAL to make its SLOT
        this->msleep(1500);
        emit bulletRequest(NULL, 1);  //Execute the SIGNAL to make its SLOT
        collideBulletThread * c = (collideBulletThread *)this->bullet->collideBullet;
        if(c->stop){
            this->stop=1;
            break;
        }
        delete this->bullet->lblBullet;
        c->stop = 1;
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
        if(this->stop){
            break;
        }
        this->msleep(100); //Time in miliseconds

        mutex.unlock();

        if(this->animation != 0)
            this->msleep(this->time);

        emit collideBulletRequest(this, this->animation);  //Execute the SIGNAL to make its SLOT
    }
}


//This is a reference to the functions below
TimeThread::TimeThread(QObject *parent):
    QThread(parent){}

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

        emit timeRequest(this->value);  //Execute the SIGNAL to make its SLOT
        this->value++;
        this->msleep(this->time);
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

        this->msleep(this->time / 2);
        int random  = this->randomize(0,23);
        this->msleep(this->time /2);
        emit trickRequest(0, random); //Execute the SIGNAL to make its SLOT
        this->msleep(this->time);
        emit trickRequest(1, random);
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
