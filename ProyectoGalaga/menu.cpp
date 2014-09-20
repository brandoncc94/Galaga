#include "mainwindow.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "ui_menu.h"
#include <QDebug>
#include <QDesktopWidget>

void centerScreen(int,int,Menu*);

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    centerScreen(400,300,this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_ingresar_clicked()
{
    MainWindow * a = new MainWindow();
    this->nombre = this->ui->nombre->text();
    a->show();
    a->load(this);
    this->hide();

}


void centerScreen(int pWidth, int pHeight, Menu *window){
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    int x = (screenWidth - pWidth) / 2;
    int y = (screenHeight - pHeight) / 2;

    window->resize(pWidth, pHeight);
    window->move(x, y);
}
