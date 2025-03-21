#include "ligne.h"

Ligne::Ligne(Point p1, Point p2)
{
    _p1 = p1;
    _p2 = p2;
}

double Ligne::angleBetweenTo(Ligne line1, Ligne line2){
    double angle1 = atan2(line1._p2._y - line1._p1._y, line1._p2._x - line1._p1._x);
    double angle2 = atan2(line2._p2._y - line2._p1._y, line2._p2._x - line2._p1._x);
    return -(angle1-angle2);
}

void Ligne::display(){
    qDebug()<<"point1: ";
    _p1.display();
    qDebug()<<"point2: ";
    _p2.display();


}
