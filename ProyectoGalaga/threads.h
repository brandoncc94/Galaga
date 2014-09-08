#ifndef THREADS_H
#define THREADS_H

#include <QThread>
//#include <estructuras.h>
//#include <QGlobal.h>
#include <QTime>

class ThreadAnimacion : public QThread
{
    Q_OBJECT
public:
    explicit ThreadAnimacion(QObject *parent = 0);
    void run();
    int tiempo = 2500;
    int stop = 0;
    int animacion = 0;

signals:
    void peticionAnimacion(int);

public slots:

};

#endif // THREADS_H

