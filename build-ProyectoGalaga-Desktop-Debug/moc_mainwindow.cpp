/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProyectoGalaga/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 16),
QT_MOC_LITERAL(4, 42, 13),
QT_MOC_LITERAL(5, 56, 7),
QT_MOC_LITERAL(6, 64, 11),
QT_MOC_LITERAL(7, 76, 12),
QT_MOC_LITERAL(8, 89, 21),
QT_MOC_LITERAL(9, 111, 13),
QT_MOC_LITERAL(10, 125, 10),
QT_MOC_LITERAL(11, 136, 17),
QT_MOC_LITERAL(12, 154, 12),
QT_MOC_LITERAL(13, 167, 20),
QT_MOC_LITERAL(14, 188, 18),
QT_MOC_LITERAL(15, 207, 18),
QT_MOC_LITERAL(16, 226, 19),
QT_MOC_LITERAL(17, 246, 15),
QT_MOC_LITERAL(18, 262, 17),
QT_MOC_LITERAL(19, 280, 14)
    },
    "MainWindow\0startThreads\0\0executeAnimation\0"
    "executeBullet\0QLabel*\0executeTime\0"
    "executeTrick\0executeEnemiesManager\0"
    "executeAttack\0bossAttack\0BossGalagaAttack*\0"
    "checkCollide\0collideBulletThread*\0"
    "checkCollideBullet\0checkCollideAttack\0"
    "collideEnemyThread*\0checkIfWinLevel\0"
    "ManagerThreadTime\0ManagerThread*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a,
       3,    1,   80,    2, 0x0a,
       4,    2,   83,    2, 0x0a,
       6,    1,   88,    2, 0x0a,
       7,    2,   91,    2, 0x0a,
       8,    1,   96,    2, 0x0a,
       9,    0,   99,    2, 0x0a,
      10,    1,  100,    2, 0x0a,
      12,    2,  103,    2, 0x0a,
      14,    2,  108,    2, 0x0a,
      15,    1,  113,    2, 0x0a,
      17,    1,  116,    2, 0x0a,
      18,    1,  119,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 19,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->startThreads(); break;
        case 1: _t->executeAnimation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->executeBullet((*reinterpret_cast< QLabel*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->executeTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->executeTrick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->executeEnemiesManager((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->executeAttack(); break;
        case 7: _t->bossAttack((*reinterpret_cast< BossGalagaAttack*(*)>(_a[1]))); break;
        case 8: _t->checkCollide((*reinterpret_cast< collideBulletThread*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->checkCollideBullet((*reinterpret_cast< collideBulletThread*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->checkCollideAttack((*reinterpret_cast< collideEnemyThread*(*)>(_a[1]))); break;
        case 11: _t->checkIfWinLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->ManagerThreadTime((*reinterpret_cast< ManagerThread*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLabel* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BossGalagaAttack* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< collideBulletThread* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< collideBulletThread* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< collideEnemyThread* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ManagerThread* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
