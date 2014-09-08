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
    ThreadAnimacion *hiloAnimacion;

private:
    Ui::MainWindow *ui;

public slots:
    void ejecutarAnimacion(int);
};

#endif // MAINWINDOW_H
