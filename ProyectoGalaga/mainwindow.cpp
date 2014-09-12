#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadGUI(this, ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}
