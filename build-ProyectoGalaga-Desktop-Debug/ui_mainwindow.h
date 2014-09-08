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
    QFrame *topFrane;
    QLCDNumber *lcdNumber;
    QLabel *label;
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
        topFrane = new QFrame(centralWidget);
        topFrane->setObjectName(QStringLiteral("topFrane"));
        topFrane->setGeometry(QRect(0, -10, 801, 61));
        topFrane->setStyleSheet(QStringLiteral("background-color: rgb(59, 141, 161);"));
        topFrane->setFrameShape(QFrame::StyledPanel);
        topFrane->setFrameShadow(QFrame::Raised);
        lcdNumber = new QLCDNumber(topFrane);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(700, 20, 81, 31));
        label = new QLabel(topFrane);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(620, 20, 66, 30));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: white;"));
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
        lblCountdown->setText(QApplication::translate("MainWindow", "CountDown", 0));
        lblGalaga->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Tiempo:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
