#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI.cpp"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->game=newGame();
    ui->setupUi(this);
    ui->lblOndas->hide();
    ui->lblGameOver->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
