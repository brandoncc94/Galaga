#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H
#include <QLabel>

//Verificar colisiones
bool check(QLabel * lblBullet,QLabel * lblEnemy,int x,int y){
    return (lblBullet->pos().x()+x < lblEnemy->pos().x() + lblEnemy->width())
            && (lblBullet->pos().y()+y < lblEnemy->pos().y() + lblEnemy->height()) &&
            (lblBullet->pos().x()+x + lblBullet->width() > lblEnemy->pos().x()) &&
            (lblBullet->pos().y()+y + lblBullet->height() > lblEnemy->pos().y());
}

//Obtener tipo según id
int getTipo(int pId){
    if(pId <= 4)
        return 5;
    else if(pId <= 8)
        return 1;
    else if(pId<=12)
        return 2;
    else if(pId<=16)
        return 4;
    else if(pId<=20)
        return 1;
    else
        return 3;
}

//Trick
QPolygon getPolygon(int pFigura){
    QPolygon polygon;
    switch(pFigura){
        case 0:
            //Estrella
            polygon << QPoint(250,110) << QPoint(190,298)
                    << QPoint(340,178) << QPoint(160,178)
                    << QPoint(310,298) << QPoint(260,110);
            break;
        case 1:
            //Triangulo
            polygon << QPoint(250,110) << QPoint(350,250)
                    << QPoint(150,250) << QPoint(260,110);
            break;
        case 2:
            //Cuadrado
            polygon << QPoint(250,110) << QPoint(350,110)
                    << QPoint(350,240) << QPoint(250,240)
                    << QPoint(260, 110);
            break;
        case 3:
            //Rombo
            polygon << QPoint(250,110) << QPoint(300,180)
                    << QPoint(250,250) << QPoint(200,180)
                    << QPoint(260, 110);
            break;
    }
    return polygon;
}


#endif // EXTRAFUNCTIONS_H
