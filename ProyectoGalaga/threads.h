#ifndef THREADS_H
#define THREADS_H

#include <QThread>
#include <QLabel>
#include "struct.h"




//Thread that handle the behavior of the martians
class AnimationThread : public QThread
{
    Q_OBJECT
public:
    explicit AnimationThread(QObject *parent = 0);
    void run();
    int time = 2500;
    int stop = 0;
    int animation = 0;

signals:
    void animationRequest(int);

public slots:

};

//Thread that handle the collide of the bullet
class collideBulletThread : public QThread
{
    Q_OBJECT
public:
    explicit collideBulletThread(QObject *parent = 0);
    void run();
    int time = 2500;
    int stop = 0;
    QLabel *lblBullet;

signals:
    void collideBulletRequest(QLabel *);

public slots:

};



//Thread that handle the behavior of the bullet
class BulletThread : public QThread
{
    Q_OBJECT
public:
    explicit BulletThread(QObject *parent = 0);
    void run();
    int time = 2500;
    int stop = 0;
    Bullet * bullet = (Bullet *)malloc(sizeof(Bullet));

signals:
    void bulletRequest(QLabel *, int);

public slots:

};


//Thread that handle the time
class TimeThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeThread(QObject *parent = 0);
    void run();
    int time = 1000;
    int stop = 0;
    int value = 0;

signals:
    void timeRequest(int);

public slots:

};
#endif // THREADS_H

