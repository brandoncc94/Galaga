#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI.cpp"

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
