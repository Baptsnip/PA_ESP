#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <QDebug>


class Point
{
public:
    Point();
    Point(double, double);
    double get_x();
    double get_y();
    void set_point(double x, double y);
    void rotate(Point pointRotation , double angle_degre);
    static double distance(Point P1, Point P2);
    double distanceFromZero();
    void display();
    void display(QString nom);

public:
    double _x=0, _y=0;
};

#endif // POINT_H
