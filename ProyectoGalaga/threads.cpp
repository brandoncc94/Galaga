#include "threads.h"    //Para manejar las funcions del thread
#include <QtCore>       //Para el Mutex
#include <iostream>
#include <ctime>
#include "mainwindow.h"

//Esto lo pongo para hacer referencia a las funcions de abajo
ThreadAnimacion::ThreadAnimacion(QObject *parent):
    QThread(parent){}

//Desarrollamos lo que quiero que pase cuando corre el Thread
void ThreadAnimacion::run(){
    while(true){
        QMutex mutex;
        mutex.lock();
        if(this->stop){
            break;
        }
        this->msleep(100);

        mutex.unlock();

        emit peticionAnimacion(this->animacion);  //Ejecutamos el SIGNAL para que haga su SLOT
        this->animacion++;
        this->msleep(this->tiempo);      //Tiempo en milisegundos de cada cuanto imprime
    }
}
