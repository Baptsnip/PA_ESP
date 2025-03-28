#ifndef MOTOR_H
#define MOTOR_H

#include <QString>

class Motor {
public:
    int steps;
    bool clockwise; // true = horaire, false = anti-horaire

    Motor() : steps(0), clockwise(true) {}

    QString getDirection() const {
        return clockwise ? "Horaire" : "Anti-horaire";
    }
};

#endif // MOTOR_H
