#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

ship * newShip(){
    return (ship*)malloc(sizeof(ship));
}

game * newGame(){
    return (game*)malloc(sizeof(game));
}

Bullet* newBullet(QLabel* lblBullet){
    Bullet * bullet = (Bullet *)malloc(sizeof(Bullet));
    bullet->lblBullet=lblBullet;
    return bullet;
}

