#include <stdio.h>
#include "struct.h"
#include <stdlib.h>

enemiesList_t *initialize(enemiesList_t *pList){
    //Reservamos el espacio de memoria de la lista y del primer nodo
    pList = (enemiesList_t *)malloc(sizeof(enemiesList_t));
    //Reservamos el espacio del primer nodo
    pList->firstNode = (enemy_t *)malloc(sizeof(enemy_t));
    //El primero es como un espacio predeterminado que apunta a NULL.
    pList->firstNode->next = NULL;
    return pList;
}

void insert(enemy_t *pTmp, int pId, int pLifes, int pType, int pIsFilled, int pPoints){
    //Recorrer hasta llegar al último nodo
    while(pTmp->next!=NULL)
        pTmp = pTmp->next;
    //Crear el nodo en la dirección al que apunta el último
    enemy_t *newEnemy = (enemy_t *)malloc(sizeof(enemy_t));
    pTmp->next = newEnemy;
    newEnemy->id = pId;
    newEnemy->lifes = pLifes;
    newEnemy->type = pType;
    newEnemy->isFilled = pIsFilled;
    newEnemy->points = pPoints;
    newEnemy->next = NULL;
}

void showEnemies(enemy_t *pTmp){
    printf("\n\tLista: \n\t\t");
    //Recorremos la lista hasta encontrar
    while(pTmp->next !=NULL){
        printf("%d %d %d %d-> ",pTmp->id, pTmp->lifes, pTmp->type, pTmp->isFilled, pTmp->points);
        pTmp = pTmp->next;
        if(pTmp->next == NULL)
            printf("%d %d %d %d-> ",pTmp->id, pTmp->lifes, pTmp->type, pTmp->isFilled, pTmp->points);
    }
}

void updateEnemies(enemy_t *pTmp, int id, int pLifes, int pType, int pIsFilled, int pPoints){
    while(pTmp->next != NULL){
        if(pTmp->id == id){
            pTmp->lifes = pLifes;
            pTmp->type = pType;
            pTmp->isFilled = pIsFilled;
            pTmp->points = pPoints;
        }
        pTmp = pTmp->next;
    }
    if(pTmp->id == id){
        pTmp->lifes = pLifes;
        pTmp->type = pType;
        pTmp->isFilled = pIsFilled;
        pTmp->points = pPoints;
    }
}

int findEnemy(enemy_t *pTmp, int pRandom){
    while(pTmp->next != NULL){
        if(pTmp->id == pRandom){
            if(pTmp->isFilled!=0)
                return -1;
            else
                return pRandom;
        }
        pTmp = pTmp->next;
    }
    if(pTmp->id == pRandom){
        if(pTmp->isFilled==0)
            return -1;
        else
            return pRandom;
    }
}


int findTypeOfEnemy(enemy_t *pTmp, int pRandom){
    while(pTmp->next != NULL){
        if(pTmp->id == pRandom){
            if(pTmp->isFilled==0)
                return -1;
            else
                return pTmp->type;
        }
        pTmp = pTmp->next;
    }
    if(pTmp->id == pRandom){
        if(pTmp->isFilled==0)
            return -1;
        else
            return pTmp->type;
    }
}

int findLifesOfEnemy(enemy_t *pTmp, int pRandom){
    while(pTmp->next != NULL){
        if(pTmp->id == pRandom){
            if(pTmp->isFilled==0)
                return -1;
            else
                return pTmp->lifes;
        }
        pTmp = pTmp->next;
    }
    if(pTmp->id == pRandom){
        if(pTmp->isFilled==0)
            return -1;
        else
            return pTmp->lifes;
    }
}
