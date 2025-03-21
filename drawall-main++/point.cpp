#include "point.h"

Point::Point()
{

}
Point::Point(double x, double y){
    _x = x;
    _y = y;
}

void Point::rotate(Point pointRotation , double angle){

    double Cx = pointRotation._x;
    double Cy = pointRotation._y;

    double temp_x = cos(angle) * (_x - Cx) - sin(angle) * (_y - Cy) + Cx;
    double temp_y = sin(angle) * (_x - Cx) + cos(angle) * (_y - Cy) + Cy;

    _x = temp_x;
    _y = temp_y;
}

double Point::distance(Point P1, Point P2){
    double localDistance = sqrt(pow(P2._x-P1._x, 2)+pow(P2._y-P1._y, 2));
    //qDebug()<<"distance = "<<localDistance<<_y;
    return localDistance;
}

double Point::distanceFromZero(){
    double localDistance = sqrt(pow(_x, 2)+pow(_y, 2));
    //qDebug()<<"distance du point zéro = "<<localDistance<<_y;
    return localDistance;
}
void Point::display(){
    qDebug()<<"x= "<<_x<<" "<<"y= "<<_y<<_y;
}

void Point::display(QString nom){
    qDebug()<<nom<<" x= "<<_x<<" "<<"y= "<<_y<<_y;
}
