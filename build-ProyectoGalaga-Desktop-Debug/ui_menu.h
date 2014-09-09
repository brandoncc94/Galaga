/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QFrame *frame;
    QLabel *labelJugador;
    QLineEdit *nombre;
    QLabel *imagenGalaga;
    QPushButton *ingresar;
    QLabel *fondo;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QStringLiteral("Menu"));
        Menu->resize(400, 300);
        frame = new QFrame(Menu);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 401, 301));
        frame->setStyleSheet(QStringLiteral(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labelJugador = new QLabel(frame);
        labelJugador->setObjectName(QStringLiteral("labelJugador"));
        labelJugador->setGeometry(QRect(30, 150, 141, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelJugador->setFont(font);
        labelJugador->setStyleSheet(QStringLiteral(""));
        nombre = new QLineEdit(frame);
        nombre->setObjectName(QStringLiteral("nombre"));
        nombre->setGeometry(QRect(180, 150, 181, 33));
        nombre->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        imagenGalaga = new QLabel(frame);
        imagenGalaga->setObjectName(QStringLiteral("imagenGalaga"));
        imagenGalaga->setGeometry(QRect(90, 30, 211, 91));
        imagenGalaga->setStyleSheet(QStringLiteral(""));
        imagenGalaga->setPixmap(QPixmap(QString::fromUtf8("../images/galaga.gif")));
        imagenGalaga->setScaledContents(true);
        ingresar = new QPushButton(frame);
        ingresar->setObjectName(QStringLiteral("ingresar"));
        ingresar->setGeometry(QRect(150, 220, 98, 31));
        ingresar->setCursor(QCursor(Qt::PointingHandCursor));
        ingresar->setStyleSheet(QStringLiteral("background-color: rgb(43, 215, 76);"));
        fondo = new QLabel(frame);
        fondo->setObjectName(QStringLiteral("fondo"));
        fondo->setGeometry(QRect(0, 0, 401, 301));
        fondo->setPixmap(QPixmap(QString::fromUtf8("../images/Main.jpg")));
        fondo->setScaledContents(true);
        fondo->raise();
        labelJugador->raise();
        nombre->raise();
        ingresar->raise();
        imagenGalaga->raise();

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QApplication::translate("Menu", "Menu", 0));
        labelJugador->setText(QApplication::translate("Menu", "<html><head/><body><p><span style=\" color:#f7f7f7;\">Nombre de Jugador:</span></p></body></html>", 0));
        imagenGalaga->setText(QString());
        ingresar->setText(QApplication::translate("Menu", "Nueva Partida", 0));
        fondo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
