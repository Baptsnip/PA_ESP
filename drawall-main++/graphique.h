#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>

class Graphique : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Graphique(QObject* parent);
    void setPointA(float x, float y);
    void setPointB(float x, float y);
    void setPen1(float x, float y,float angle);
    //void setcourroieG(float x, float y);
    //void setcourroieD(float x, float y);
    void setPoints(const std::vector<QPointF>& points);
protected:
    //void paintEvent(QPaintEvent *event) override();

private slots:
    void avancerChariot();  // Animation du chariot

private:
    QGraphicsScene *m_scene;
    QGraphicsEllipseItem *m_pointA = nullptr;
    QGraphicsEllipseItem *m_pointB = nullptr;
    QGraphicsEllipseItem *m_Pen1 = nullptr;
    QGraphicsEllipseItem *m_Pen2 = nullptr;
    QGraphicsLineItem *m_CourroieG = nullptr;
    QGraphicsLineItem *m_CourroieD = nullptr;
    QGraphicsRectItem *m_vitrine =  nullptr;
    QGraphicsRectItem *m_y0 = nullptr;
    QGraphicsRectItem *m_y1 = nullptr;
    QGraphicsRectItem *m_y2 = nullptr;
    QGraphicsRectItem *m_y3 = nullptr;
    QGraphicsRectItem *m_c1 = nullptr;
    QGraphicsRectItem *m_c2 = nullptr;
    QGraphicsItemGroup *myGroup = nullptr;
    QTimer animationTimer;
    std::vector<QPointF> trajectoire;
    int index;

signals:

};

#endif // GRAPHIQUE_H
