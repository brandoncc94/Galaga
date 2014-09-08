#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadGUI(this, ui);
    hiloAnimacion = new ThreadAnimacion(this);
    connect(hiloAnimacion,SIGNAL(peticionAnimacion(int)),this, SLOT(ejecutarAnimacion(int))); //Cuando este thread sea ejecutado...
    hiloAnimacion->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->lblShip->y() >= 430)
        ui->lblShip->move(ui->lblShip->x(),430);
    else if(ui->lblShip->y() <= 20)
        ui->lblShip->move(ui->lblShip->x(),430);
    if(ui->lblShip->x() >= 660)
        ui->lblShip->move(660,ui->lblShip->y());
    else if(ui->lblShip->x() <= 80)
        ui->lblShip->move(80,ui->lblShip->y());
    int x = ui->lblShip->x();
    int y = ui->lblShip->y();

    switch(event->key()){
        case Qt::Key_Space:
            //Shot
            break;
        case Qt::Key_Up && Qt::Key_Right:
            ui->lblShip->setPixmap(QPixmap("../images/fastShipRight.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(154);
            ui->lblShip->move(QPoint(x + 10, y-10));
            event->accept();
            break;
        case Qt::Key_Up:
            ui->lblShip->setPixmap(QPixmap("../images/fastShip.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(154);
            ui->lblShip->move(QPoint(x, y-10));
            event->accept();
            break;
        case Qt::Key_Down:
            ui->lblShip->move(QPoint(x, y+10));
            event->accept();
            break;
        case Qt::Key_Left:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipLeft.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(122);
            ui->lblShip->setFixedWidth(66);
            ui->lblShip->move(QPoint(x-10, y));
            event->accept();
            break;
        case Qt::Key_Right:
            ui->lblShip->setPixmap(QPixmap("../images/normalShipRight.png", 0, Qt::AutoColor));
            ui->lblShip->setFixedHeight(122);
            ui->lblShip->setFixedWidth(66);
            ui->lblShip->move(QPoint(x+10, y));
            event->accept();
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    ui->lblShip->setPixmap(QPixmap("../images/normalShip.png", 0, Qt::AutoColor));
    ui->lblShip->setFixedHeight(122);
    ui->lblShip->setFixedWidth(100);
}
