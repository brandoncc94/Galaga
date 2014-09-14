#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

ship * newShip(){
    return (ship*)malloc(sizeof(ship));
}

Game * newGame(){
    user * u= (user*)malloc(sizeof(user));
    Game * g= (Game*)malloc(sizeof(Game));
    g->player=u;
    return g;
}

Bullet* newBullet(QLabel* lblBullet){
    Bullet * bullet = (Bullet *)malloc(sizeof(Bullet));
    bullet->lblBullet=lblBullet;
    return bullet;
}


