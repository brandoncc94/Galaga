#include "mainwindow.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
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
    //http://qt-project.org/faq/answer/how_can_i_convert_a_qstring_to_char_and_vice_versa qPrintable solo para imprimir
    //char * s= "hola";
    //ui->nombre->setText(QString::fromLocal8Bit(s));
    //Coversion de qstring a char * printf("%s",this->ui->nombre->text().toLocal8Bit().data());
    MainWindow * a = new MainWindow();
    a->game->player->name=this->ui->nombre->text().toLocal8Bit().data();
    printf("%s",a->game->player->name);
    a->show();
    a->load();
    this->hide();

}
