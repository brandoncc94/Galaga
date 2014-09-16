#ifndef STRUCT_H
#define STRUCT_H

#include <QLabel>

typedef struct ship{
    int disparos;
}ship;


typedef struct Bullet{
    QLabel * lblBullet;
    void * collideBullet;
}Bullet;

typedef struct user{
    char *name;
    int score;
    int lifes;
}user;

typedef struct Game{
    user *player;
    int nivel;
}Game;

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
Game* newGame();
#endif // STRUCT_H
