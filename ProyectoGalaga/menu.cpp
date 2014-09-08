#include "mainwindow.h"
#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_ingresar_clicked()
{
    MainWindow * a = new MainWindow();
    a->show();
    this->hide();

}
