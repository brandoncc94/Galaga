#include "mainwindow.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu w;
    //AQUI ESTA EL CAMBIO
    w.show();

    return a.exec();
}
