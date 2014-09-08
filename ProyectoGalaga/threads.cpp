#include "threads.h"    //Para manejar las funcions del thread
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
        this->msleep(100); //Time in miliseconds

        mutex.unlock();

        emit animationRequest(this->animation);  //Execute the SIGNAL to make its SLOT

        this->msleep(this->time);
        if(this->animation == 6)
            this->animation--;
        else
            this->animation++;
    }
}

//This is a reference to the functions below
BulletThread::BulletThread(QObject *parent):
    QThread(parent){}

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

        emit bulletRequest(this->lblBullet, 0);  //Execute the SIGNAL to make its SLOT
        this->msleep(1500);
        this->stop = 1;
        delete this->lblBullet;
        emit bulletRequest(NULL, 1);  //Execute the SIGNAL to make its SLOT
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
