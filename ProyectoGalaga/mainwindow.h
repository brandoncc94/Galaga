#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threads.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AnimationThread *animationThread;
    BulletThread *bulletThread;
    TimeThread *timeThread;

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
};

#endif // MAINWINDOW_H
