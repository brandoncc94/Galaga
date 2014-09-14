#ifndef THREADS_H
#define THREADS_H

#include <QThread>
#include <QLabel>
#include <struct.h>

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
    int animation = 0;
    QLabel *lblBullet;

signals:
    void collideBulletRequest(collideBulletThread *, int);

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

//Thread that handle the tricks
class TrickThread : public QThread
{
    Q_OBJECT
public:
    explicit TrickThread(QObject *parent = 0);
    void run();
    int time = 4000;
    int stop = 0;
    int randomize(int,int);

signals:
    void trickRequest(int, int);

public slots:

};

//Thread that handle the behavior of the bullet
class EnemiesManager : public QThread
{
    Q_OBJECT
public:
    explicit EnemiesManager(QObject *parent = 0);
    void run();
    int time = 100;
    int stop = 0;
    int id = 0;
    enemiesList_t *enemiesList;

signals:
    void enemiesManagerRequest(int);

public slots:

};

#endif // THREADS_H

