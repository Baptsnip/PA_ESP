#include "chariot.h"
#include <QtDebug>
#include <cmath>

Chariot::Chariot(configuration config)
{
    _A = config.mesureA; // distance horizontale entre le point A et le point C
    _B = config.mesureB; // distance horizontale entre le point B et le point C
    _C = config.mesureC; // distance verticale entre le C et les points A et B
    _D = config.mesureD; // distance entre les moteurs
    _config = config;
}

float Chariot::calcul_longueurCourroieGauche() {
    return sqrt(pow(this->_PA._x, 2) + pow(this->_PA._y, 2));
}

float Chariot::calcul_longueurCourroieDroite() {
    return sqrt(pow(this->_PB._x, 2) + pow(this->_PB._y, 2));
}

float Chariot::somme_moment(float Xpen, float Ypen, float angle) {
    Point pointRotation;
    pointRotation._x = Xpen;
    pointRotation._y = Ypen;

    float _angle = angle;

    _PC._x = Xpen - _config.deportx;
    _PC._y = Ypen - _config.deporty;
    _PC.rotate(pointRotation, _angle);

    _PA._x = _PC._x - _A;
    _PA._y = _PC._y - _C;
    _PB._x = _PC._x + _B;
    _PB._y = _PC._y - _C;

    _PA.rotate(_PC, _angle);
    _PB.rotate(_PC, _angle);

    Point P0(0, 0);
    Point projet_PA(_PA._x, 0);
    Ligne beltA(P0, _PA);
    Ligne ProjectionPA(P0, projet_PA);
    double alpha = Ligne::angleBetweenTo(beltA, ProjectionPA);

    Point pointMoteurDroit(_D, 0);
    Point projet_PB(_PB._x, 0);
    Ligne beltB(pointMoteurDroit, _PB);
    Ligne ProjectionPB(pointMoteurDroit, projet_PB);
    double beta = -Ligne::angleBetweenTo(beltB, ProjectionPB);

    float TA = cos(beta) / sin(alpha + beta);
    float TB = cos(alpha) / sin(alpha + beta);

    Vecteur brasDeLevierA(_PA._x - _PC._x, _PA._y - _PC._y);
    Vecteur brasDeLevierB(_PB._x - _PC._x, _PB._y - _PC._y);

    Vecteur VecteurTensionA(P0, _PA, TA);
    Vecteur VecteurTensionB(pointMoteurDroit, _PB, TB);

    float moduleTA = Vecteur::moduleProduitVec(brasDeLevierA, VecteurTensionA);
    float moduleTB = Vecteur::moduleProduitVec(brasDeLevierB, VecteurTensionB);

    return moduleTA + moduleTB;
}

float Chariot::calculAngleEquilibre(float Xpen, float Ypen) {
    float angle = 45 * M_PI / 180;  // angle initial
    float epsilon = 0.001;
    int maxIterations = 100;
    float sommeMoment = 0;
    float sommeMomentEpsilonInclinaison = 0;
    float lastAngle = angle;

    int iteration = 0;

    while (iteration < maxIterations) {
        iteration++;

        sommeMoment = somme_moment(Xpen, Ypen, angle);
        if (fabs(sommeMoment) < 0.001) {
            break; // convergence atteinte
        }

        sommeMomentEpsilonInclinaison = somme_moment(Xpen, Ypen, angle + epsilon);
        float derivee = (sommeMomentEpsilonInclinaison - sommeMoment) / epsilon;

        if (fabs(derivee) < 0.00001) {
            qDebug() << "[SECURITE] Dérivée trop faible, sortie anticipée.";
            break;
        }

        float correction = sommeMoment / derivee;

        // Limitation de la correction pour éviter les sauts violents
        if (fabs(correction) > 0.2)
            correction = 0.2 * (correction > 0 ? 1 : -1);

        lastAngle = angle;
        angle -= correction;

        qDebug() << "=== Iteration: " << iteration;
        qDebug() << "Angle (°): " << angle * 180 / M_PI;
        qDebug() << "Somme moment = " << sommeMoment;
        qDebug() << "Correction = " << correction;
        qDebug() << "Longueur courroie G : " << calcul_longueurCourroieGauche();
        qDebug() << "Longueur courroie D : " << calcul_longueurCourroieDroite();
    }

    if (iteration >= maxIterations) {
        qDebug() << "[ALERTE] Angle non trouvé après " << maxIterations << " itérations. Dernier angle utilisé : " << lastAngle * 180 / M_PI;
        return lastAngle; // on retourne le dernier angle connu
    }

    return angle;
}

void Chariot::getPointAB(float penX, float penY, float &ax, float &ay, float &bx, float &by, float &px, float &py) {
    this->calculAngleEquilibre(penX, penY);
    ax = this->_PA._x;
    ay = this->_PA._y;
    bx = this->_PB._x;
    by = this->_PB._y;
    px = this->_PC._x;
    py = this->_PC._y;
}
