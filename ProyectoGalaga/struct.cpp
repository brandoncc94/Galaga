#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

ship * newShip(){
    return (ship*)malloc(sizeof(ship));
}

game * newGame(){
    return (game*)malloc(sizeof(game));
}

enemy * newEnemy(){
    return (enemy*)malloc(sizeof(game));
}

enemyLine * newEnemyLine(){
    return (enemyLine*)malloc(sizeof(enemyLine));
}

matrixEnemy * newMatrixEnemy(){
    matrixEnemy* me = (matrixEnemy*)malloc(sizeof(matrixEnemy));
    me->line = newEnemyLine();
    return me;
}

Bullet* newBullet(QLabel* lblBullet){
    Bullet * bullet = (Bullet *)malloc(sizeof(Bullet));
    bullet->lblBullet=lblBullet;
    return bullet;
}

