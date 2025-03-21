#ifndef CHARIOT_H
#define CHARIOT_H
#include "point.h"
#include "vitrine.h"
#include "ligne.h"
#include "configuration.h"
#include "vecteur.h"

class Chariot
{
public:
    //Chariot(float mesureA, float mesureB, float mesureC, Point offsetPen, vitrine vit );
    Chariot(configuration config);
    void equilibrage(Point pen);
    float get_beltX();
    float get_beltY();
    void getPointAB(float penX, float penY, float &ax, float &ay, float &bx, float &by, float &px, float &py);

private:
    configuration _config;



private:
    vitrine _vit;
    float _A, _B, _C, _D;

    Point _offsetPen;

    float calcul_longueurCourroieGauche();
    float calcul_longueurCourroieDroite();
    float somme_moment(float Xpen, float Ypen, float angle);

public:
    float calculAngleEquilibre(float Xpen, float Ypen);
    Point _PA, _PB, _PC;
};

#endif // CHARIOT_H
