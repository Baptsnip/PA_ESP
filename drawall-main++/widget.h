#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLineEdit> // Pour le QLineEdit
//#include "point.h"
#include "configuration.h"
#include "chariot.h"
#include "graphique.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    double getSaisie() const; // Getter pour obtenir la valeur saisie

private slots:
    void onButtonClicked(); // Déclarez votre slot ici
    void onTextChanged(const QString &text);
    void onEnvoyerGCode();


private:
    Ui::Widget *ui;
    configuration maConfig;
    Graphique *m_graphique;
    QLineEdit *lineEdit;     // Déclarez un QLineEdit membre
    double saisie;

    QLineEdit *xLineEdit;    // Champ de saisie pour X
    QLineEdit *yLineEdit;    // Champ de saisie pour Y
    GCode gcode;





};
#endif // WIDGET_H
