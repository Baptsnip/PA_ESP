#include "graphique.h"
#include <cmath> // Pour les calculs trigonométriques

Graphique::Graphique(QObject* parent) : QGraphicsScene(parent)
{
    // Initialisation des variables
    float ax = 0, ay = 0, bx = 0, by = 0, px = 0, py = 0;

    // Création des éléments individuels
    m_vitrine = new QGraphicsRectItem(0, 0, 900, 800);
    m_pointA = new QGraphicsEllipseItem(ax, ay, 10, 10);
    m_pointA->setBrush(QBrush(Qt::red));
    m_pointB = new QGraphicsEllipseItem(bx, by, 10, 10);
    m_pointB->setBrush(QBrush(Qt::blue));
    m_Pen1 = new QGraphicsEllipseItem(px, py, 10, 10);
    m_Pen2 = new QGraphicsEllipseItem(px, py, 10, 10);
    m_CourroieG = new QGraphicsLineItem(0, 0, ax, ay);
    m_CourroieD = new QGraphicsLineItem(900, 0, bx, by);

    // Création des éléments à regrouper avec les décalages relatifs
    m_y0 = new QGraphicsRectItem(-5, -40, 20, 100);  // (x-5, y-40)
    m_y1 = new QGraphicsRectItem(-33, -40, 80, 20);  // (x-33, y-40)
    m_y2 = new QGraphicsRectItem(50, -10, 60, 20);   // (x+30, y-40)
    m_y2->setRotation(-45);
    m_y3 = new QGraphicsRectItem(-100, -20, 60, 20);  // (x-60, y-83)
    m_y3->setRotation(45);
    m_c1 = new QGraphicsRectItem(-5, 0, 50, 10);     // (x-5, y)
    m_c2 = new QGraphicsRectItem(-35, 10, 50, 10);    // (x-35, y+10)

    // Création d'un groupe pour les éléments m_y0, m_y1, m_y2, m_y3, m_c1, m_c2
    myGroup = new QGraphicsItemGroup();
    myGroup->addToGroup(m_y0);
    myGroup->addToGroup(m_y1);
    myGroup->addToGroup(m_y2);
    myGroup->addToGroup(m_y3);
    myGroup->addToGroup(m_c1);
    myGroup->addToGroup(m_c2);

    // Ajout du groupe à la scène
    this->addItem(m_vitrine);
    this->addItem(m_pointA);
    this->addItem(m_pointB);
    this->addItem(m_Pen1);
    this->addItem(m_Pen2);
    this->addItem(m_CourroieG);
    this->addItem(m_CourroieD);
    this->addItem(myGroup);

    connect(&animationTimer, &QTimer::timeout, this, &Graphique::avancerChariot);
}

void Graphique::setPoints(const std::vector<QPointF>& points) {
    Interpolation interpol;
    interpol.setPoints(points);
    trajectoire = interpol.getInterpolatedPoints(20);

    // Afficher la trajectoire
    for (size_t i = 1; i < trajectoire.size(); ++i) {
        addLine(trajectoire[i-1].x(), trajectoire[i-1].y(),
                trajectoire[i].x(), trajectoire[i].y(),
                QPen(Qt::blue));
    }

    // Lancer l'animation
    index = 0;
    animationTimer.start(50);  // Vitesse de mise à jour (50 ms)
}

void Graphique::avancerChariot() {
    if (index < trajectoire.size()) {
        chariot->setPos(trajectoire[index]);
        index++;
    } else {
        animationTimer.stop();
    }
}

void Graphique::setPointA(float x, float y){
    this->m_pointA->setPos(x, y);
    this->m_CourroieG->setLine(0, 0, x, y);
}

void Graphique::setPointB(float x, float y){
    this->m_pointB->setPos(x, y);
    this->m_CourroieD->setLine(900, 0, x, y);
}

void Graphique::setPen1(float x, float y, float angle){
    // Déplacer le groupe en fonction de (x, y)
    myGroup->setPos(x, y);

    // Rotation du groupe en fonction de l'angle
    myGroup->setRotation(angle);

    // Les positions des éléments dans le groupe sont relatives, donc elles se déplacent correctement
    // Exemple de position de m_Pen1 (relative au groupe) :
    m_Pen1->setPos(x + 35, y);  // Déplacement du crayon
    m_Pen2->setPos(x - 35, y+10);

    // Maintenir les décalages relatifs des autres éléments
   /* m_y0->setPos(x - 5, y - 40);
    m_y1->setPos(x - 33, y - 40);
    m_y2->setPos(x + 30, y - 40);
    m_y3->setPos(x - 60, y - 83);
    m_c1->setPos(x - 5, y);
    m_c2->setPos(x - 35, y + 10);*/
}



/*
#include "graphique.h"

Graphique::Graphique(QObject* parent) : QGraphicsScene(parent)
{
T1=T2cosβcosα(7)

    //m_scene = new QGraphicsScene();

    float ratio = 0.8;
    float ax=0,ay=0,bx=0,by=0,px=0,py=0;
    m_vitrine = new QGraphicsRectItem(0,0,900,800);
    m_pointA = new QGraphicsEllipseItem(ax,ay,10,10);
    m_pointB = new QGraphicsEllipseItem(bx,by,10,10);
    m_Pen1 = new QGraphicsEllipseItem(px,py,10,10);
    m_CourroieG = new QGraphicsLineItem(0, 0, ax, ay);
    m_CourroieD = new QGraphicsLineItem(900, 0, bx, by); //900 or 880 (configuration.h)

    //reussir a faire en sorte que ça tourne avec et non que ça reste figer
    m_y0 = new QGraphicsRectItem(px,py, 20, 100);
    m_y1 = new QGraphicsRectItem(px,py, 80, 20);
    m_y2 = new QGraphicsRectItem(px,py, 60, 20);
    m_y2->setRotation(-45);
    m_y3 = new QGraphicsRectItem(px,py, 60, 20);
    m_y3->setRotation(+45);
    m_c1 = new QGraphicsRectItem(px,py, 50, 10);
    m_c2 = new QGraphicsRectItem(px,py, 50, 10);

    /*
    //group all above
    QGraphicsItemGroup * myGroup = new QGraphicsItemGroup();
    myGroup->addToGroup(m_y0);
*/
/*
    myGroup->addToGroup(m_y1);
    myGroup->addToGroup(m_y2);
    myGroup->addToGroup(m_y3);
    myGroup->addToGroup(m_c1);
    myGroup->addToGroup(m_c2);
    */

/*
this->addItem(m_vitrine);
this->addItem(m_pointA);
this->addItem(m_pointB);
this->addItem(m_Pen1);
this->addItem(m_CourroieG);
this->addItem(m_CourroieD);

this->addItem(m_y0);
this->addItem(m_y1);
this->addItem(m_y2);
this->addItem(m_y3);
this->addItem(m_c1);
this->addItem(m_c2);

//this->addItem(myGroup);

//carriage.getPointAB()


}


void Graphique::setPointA(float x, float y){
    this->m_pointA->setPos(x,y);
    this->m_CourroieG->setLine(0, 0, x, y);
}

void Graphique::setPointB(float x, float y){
    this->m_pointB->setPos(x,y);
    this->m_CourroieD->setLine(900, 0, x, y);
}


void Graphique::setPen1(float x, float y, float angle){
    //this->m_Pen1->setPos(x,y);
    this->m_Pen1->setPos(x+35,y); //decalage crayon
    this->m_y0->setPos(x-5,y-40);
    this->m_y1->setPos(x-33,y-40);
    this->m_y2->setPos(x+30,y-40);
    this->m_y3->setPos(x-60,y-83);
    this->m_c1->setPos(x-5,y);
    this->m_c2->setPos(x-35,y+10);
    m_Pen1->setRotation(angle);
    m_y0->setRotation(angle);
    m_y1->setRotation(angle);
    m_y2->setRotation(angle);
    m_y3->setRotation(angle);
    m_c1->setRotation(angle);
    m_c2->setRotation(angle);

}


/*
void Graphique::setcourroieG(float x, float y){
    this->m_CourroieG->setPos(x,y);
}

void Graphique::setcourroieD(float x, float y){
    this->m_CourroieD->setPos(x,y);
}

*/
