#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threads.h"
#include "struct.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();
    Game* game;
    AnimationThread *animationThread;
    BulletThread *bulletThread;
    TimeThread *timeThread;
    TrickThread *trickThread;
    EnemiesManager *enemiesManagerThread;

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    //General
    void startThreads();

    //Animation
    void executeAnimation(int);

    //Bullet
    void executeBullet(QLabel *, int);

    //Time
    void executeTime(int);

    //Enemy Fly
    void executeFly(int);

    //Trick
    void executeTrick(int, int);

    //EnemiesManager
    void executeEnemiesManager(int);
    
    //Check Collide
    void checkCollide(collideBulletThread *, int);
};

#endif // MAINWINDOW_H
