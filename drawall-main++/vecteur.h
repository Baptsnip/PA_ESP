#ifndef VECTEUR_H
#define VECTEUR_H
#include "point.h"


class Vecteur
{
public:
    //définition d'un vecteur par ses coordonnées x et y
    Vecteur(float x, float y);
    //définition d'un vecteur supporté par un segment de droite
    Vecteur(Point p1, Point p2, float module);
    float coord_X, coord_Y;
    static float moduleProduitVec(Vecteur u, Vecteur v);
};

#endif // VECTEUR_H

