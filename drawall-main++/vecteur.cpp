#include "vecteur.h"
Vecteur:: Vecteur(float x, float y){
    coord_X = x;
    coord_Y = y;
}

Vecteur::Vecteur(Point p1, Point p2, float module)
{
    Point _point1 = p1;
    Point _point2 = p2;
    float distance = Point::distance(_point1, _point2);
    float x = _point1._x - _point2._x;
    float y = _point1._y - _point2._y;
    coord_X = x * module / distance;
    coord_Y = y * module / distance;
}

float Vecteur::moduleProduitVec(Vecteur u, Vecteur v){
    float module = (u.coord_X * v.coord_Y ) - (u.coord_Y * v.coord_X);
    return module;
}

