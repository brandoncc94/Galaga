#ifndef STRUCT_H
#define STRUCT_H

#include <QLabel>
#include <threads.h>



typedef struct ship{
    int disparos;
}ship;


typedef struct Bullet{
    QLabel * lblBullet;
    void * collideBullet;
}Bullet;


typedef struct game{
    char* jugador;
    int puntuacion;
    int vidas;
    int nivel;
}game;

typedef struct enemy{
    int vidas;
    int tipo;
}enemy;

typedef struct enemyLine{
    enemy * enemigos;
    enemyLine * sigte;
}enemyLine;

typedef struct matrixEnemy{
    enemyLine * line;
}matrixEnemy;


#endif // STRUCT_H
