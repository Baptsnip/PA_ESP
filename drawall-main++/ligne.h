#ifndef LIGNE_H
#define LIGNE_H
#include "point.h"

class Ligne
{
public:
    Ligne();
    Ligne(Point, Point);
    static double angleBetweenTo(Ligne, Ligne);
public:
    Point _p1;
    Point _p2;
    void display();

};

#endif // LIGNE_H
