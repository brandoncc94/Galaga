/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblShip;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *martiansContainer;
    QLabel *lblCountdown;
    QLabel *lblGalaga;
    QFrame *topFrame;
    QLCDNumber *lcdTime;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *lcdHighscore;
    QLabel *label_3;
    QLabel *namePlayer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblShip = new QLabel(centralWidget);
        lblShip->setObjectName(QStringLiteral("lblShip"));
        lblShip->setGeometry(QRect(340, 440, 100, 122));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 50, 611, 511));
        martiansContainer = new QVBoxLayout(verticalLayoutWidget);
        martiansContainer->setSpacing(6);
        martiansContainer->setContentsMargins(11, 11, 11, 11);
        martiansContainer->setObjectName(QStringLiteral("martiansContainer"));
        martiansContainer->setContentsMargins(0, 0, 0, 0);
        lblCountdown = new QLabel(centralWidget);
        lblCountdown->setObjectName(QStringLiteral("lblCountdown"));
        lblCountdown->setGeometry(QRect(0, 0, 500, 281));
        lblGalaga = new QLabel(centralWidget);
        lblGalaga->setObjectName(QStringLiteral("lblGalaga"));
        lblGalaga->setGeometry(QRect(200, 0, 411, 181));
        topFrame = new QFrame(centralWidget);
        topFrame->setObjectName(QStringLiteral("topFrame"));
        topFrame->setGeometry(QRect(0, -10, 801, 61));
        topFrame->setStyleSheet(QStringLiteral(""));
        topFrame->setFrameShape(QFrame::StyledPanel);
        topFrame->setFrameShadow(QFrame::Raised);
        lcdTime = new QLCDNumber(topFrame);
        lcdTime->setObjectName(QStringLiteral("lcdTime"));
        lcdTime->setGeometry(QRect(720, 20, 61, 31));
        lcdTime->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        label = new QLabel(topFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(650, 20, 66, 30));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        label_2 = new QLabel(topFrame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 20, 66, 30));
        label_2->setFont(font);
        label_2->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lcdHighscore = new QLCDNumber(topFrame);
        lcdHighscore->setObjectName(QStringLiteral("lcdHighscore"));
        lcdHighscore->setGeometry(QRect(410, 20, 61, 31));
        lcdHighscore->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        label_3 = new QLabel(topFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 66, 30));
        label_3->setFont(font);
        label_3->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        namePlayer = new QLabel(topFrame);
        namePlayer->setObjectName(QStringLiteral("namePlayer"));
        namePlayer->setGeometry(QRect(120, 20, 191, 30));
        namePlayer->setFont(font);
        namePlayer->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lblShip->setText(QApplication::translate("MainWindow", "Ship", 0));
        lblCountdown->setText(QString());
        lblGalaga->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Tiempo:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Puntaje:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Nombre:", 0));
        namePlayer->setText(QApplication::translate("MainWindow", "Prueba", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
