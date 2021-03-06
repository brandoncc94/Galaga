#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threads.h"
#include "struct.h"
#include "menu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load(Menu *);
    int running=0;
    Game* game;
    AnimationThread *animationThread;
    BulletThread *bulletThread;
    TimeThread *timeThread;
    TrickThread *trickThread;
    EnemiesManager *enemiesManagerThread;
    EnemiesAttack * enemiesAttackThread;

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void AttackKamikaze(int);
    void AttackBullet(int);
    void AttackFlying(int);
    void AttackBossGalaga(int);



public slots:
    //General
    void startThreads();

    //Animation
    void executeAnimation(int);

    //Bullet
    void executeBullet(QLabel *, int);

    //Time
    void executeTime(int);

    //Trick
    void executeTrick(int, int);

    //EnemiesManager
    void executeEnemiesManager(int);

    //EnemiesAttack
    void executeAttack();
    void bossAttack(BossGalagaAttack*);
    
    //Check Collide
    void checkCollide(collideBulletThread *, int);
    void checkCollideBullet(collideBulletThread *, int);


    //Check Collide Attack
    void checkCollideAttack(collideEnemyThread*);
    void checkIfWinLevel();

    void stopThreads();


    void ManagerThreadTime(ManagerThread *);
};

#endif // MAINWINDOW_H
