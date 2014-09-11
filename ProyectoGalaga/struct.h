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


typedef struct enemyLine{
    enemy * enemigos;
    enemyLine * sigte;
}enemyLine;

typedef struct matrixEnemy{
    enemyLine * line;
}matrixEnemy;
<<<<<<< HEAD
*/


typedef struct enemy{
    int id;
    int lifes;
    int type;
    int isFilled;
    struct enemy *next;
}enemy_t;

typedef struct enemiesList{
    enemy_t *firstNode;
}enemiesList_t;

//Function prototypes
enemiesList_t *initialize(enemiesList_t *pList);
void insert(enemy_t *tmp, int id, int pLifes, int pType, int pIsFilled);
void showEnemies(enemy_t *tmp);
void updateEnemies(enemy_t *pTmp, int id, int pLifes, int pType, int pIsFilled);
int findEnemy(enemy_t *tmp, int pRandom);
=======


>>>>>>> f278513220fb2027c816d2095b72df25ba836d33
#endif // STRUCT_H