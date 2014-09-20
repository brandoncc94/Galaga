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
    QLabel *lblPlayerName;
    QLabel *lblNivel;
    QLCDNumber *lcdLevel;
    QLabel *lblOndas;
    QLabel *lblGameOver;
    QLabel *lblShip_2;
    QLabel *lblShip_3;
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
        lblShip->setGeometry(QRect(340, 440, 40, 60));
        lblShip->setMinimumSize(QSize(40, 60));
        lblShip->setMaximumSize(QSize(40, 60));
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
        label_2->setGeometry(QRect(300, 20, 66, 30));
        label_2->setFont(font);
        label_2->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lcdHighscore = new QLCDNumber(topFrame);
        lcdHighscore->setObjectName(QStringLiteral("lcdHighscore"));
        lcdHighscore->setGeometry(QRect(380, 20, 61, 31));
        lcdHighscore->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        label_3 = new QLabel(topFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 71, 30));
        label_3->setFont(font);
        label_3->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lblPlayerName = new QLabel(topFrame);
        lblPlayerName->setObjectName(QStringLiteral("lblPlayerName"));
        lblPlayerName->setGeometry(QRect(110, 20, 191, 30));
        lblPlayerName->setFont(font);
        lblPlayerName->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lblNivel = new QLabel(topFrame);
        lblNivel->setObjectName(QStringLiteral("lblNivel"));
        lblNivel->setGeometry(QRect(510, 20, 66, 30));
        lblNivel->setFont(font);
        lblNivel->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lcdLevel = new QLCDNumber(topFrame);
        lcdLevel->setObjectName(QStringLiteral("lcdLevel"));
        lcdLevel->setGeometry(QRect(550, 20, 61, 31));
        lcdLevel->setStyleSheet(QLatin1String("background: none;\n"
"color: white;"));
        lblOndas = new QLabel(centralWidget);
        lblOndas->setObjectName(QStringLiteral("lblOndas"));
        lblOndas->setGeometry(QRect(322, 345, 100, 100));
        lblOndas->setPixmap(QPixmap(QString::fromUtf8("../images/ondas.png")));
        lblOndas->setScaledContents(true);
        lblGameOver = new QLabel(centralWidget);
        lblGameOver->setObjectName(QStringLiteral("lblGameOver"));
        lblGameOver->setGeometry(QRect(130, 90, 531, 301));
        QFont font1;
        font1.setPointSize(20);
        lblGameOver->setFont(font1);
        lblGameOver->setPixmap(QPixmap(QString::fromUtf8("../images/GameOver.png")));
        lblGameOver->setScaledContents(true);
        lblShip_2 = new QLabel(centralWidget);
        lblShip_2->setObjectName(QStringLiteral("lblShip_2"));
        lblShip_2->setGeometry(QRect(70, 500, 40, 60));
        lblShip_2->setMinimumSize(QSize(40, 60));
        lblShip_2->setMaximumSize(QSize(40, 60));
        lblShip_2->setPixmap(QPixmap(QString::fromUtf8("../images/normalShip.png")));
        lblShip_2->setScaledContents(true);
        lblShip_3 = new QLabel(centralWidget);
        lblShip_3->setObjectName(QStringLiteral("lblShip_3"));
        lblShip_3->setGeometry(QRect(20, 500, 40, 60));
        lblShip_3->setMinimumSize(QSize(40, 60));
        lblShip_3->setMaximumSize(QSize(40, 60));
        lblShip_3->setPixmap(QPixmap(QString::fromUtf8("../images/normalShip.png")));
        lblShip_3->setScaledContents(true);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Galaga", 0));
        lblShip->setText(QApplication::translate("MainWindow", "Ship", 0));
        lblCountdown->setText(QString());
        lblGalaga->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Tiempo:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Puntaje:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Nombre::", 0));
        lblPlayerName->setText(QApplication::translate("MainWindow", "Prueba", 0));
        lblNivel->setText(QApplication::translate("MainWindow", "Nivel:", 0));
        lblOndas->setText(QString());
        lblGameOver->setText(QString());
        lblShip_2->setText(QString());
        lblShip_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
