#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T15:16:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoGalaga
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    GUI.cpp \
    threads.cpp \
    menu.cpp

HEADERS  += mainwindow.h \
    threads.h \
    menu.h

FORMS    += mainwindow.ui \
    menu.ui
