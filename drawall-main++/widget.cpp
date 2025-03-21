#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QDoubleValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    layout->addWidget(boutonGCode);
    connect(boutonGCode, &QPushButton::clicked, this, &Widget::onEnvoyerGCode);

    ui->setupUi(this);
    m_graphique = new Graphique(parent);
    ui->graphicsView->setScene(m_graphique);
    // Ajout du widget graphique personnalisé à la scène
    //graphWidget = new GraphWidget(this);
    //scene->addWidget(graphWidget);


    QVBoxLayout *mainLayout = new QVBoxLayout(this); // Crée un nouveau layout vertical principal
    setLayout(mainLayout); // Définit le layout principal pour le widget

    QSpacerItem *spacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(spacer); // Ajoute un espace flexible

    // Création et configuration du QLineEdit
    // Création des QLineEdit pour X et Y
    xLineEdit = new QLineEdit(this);
    xLineEdit->setPlaceholderText("Entrez la coordonnée X...");
    xLineEdit->setFixedSize(300, 50);

    yLineEdit = new QLineEdit(this);
    yLineEdit->setPlaceholderText("Entrez la coordonnée Y...");
    yLineEdit->setFixedSize(300, 50);

    // Créer un validateur avec une plage pour X et Y
    double minValue = 0.0;  // Valeur minimum
    double maxValue = 900.0;   // Valeur maximum
    int precision = 2;         // Précision pour les nombres décimaux

    QDoubleValidator *validator = new QDoubleValidator(minValue, maxValue, precision, this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    // Appliquer le validateur aux QLineEdits
    xLineEdit->setValidator(validator);
    yLineEdit->setValidator(validator);


    // Ajout des champs de saisie au layout principal
    mainLayout->addWidget(xLineEdit);
    mainLayout->addWidget(yLineEdit);

    // Connecter le bouton pour utiliser les valeurs saisies
    connect(ui->pushButton, &QPushButton::clicked, [this]() {
        bool xOk, yOk;
        double xValue = xLineEdit->text().replace(",", ".").toDouble(&xOk);
        double yValue = yLineEdit->text().replace(",", ".").toDouble(&yOk);


    /*
    Point p1(70,60);qDebug() << "Mise à jour de l'angle =" << angle * 180 / 3.14;
    Point p2(20,10);
    //p1.display();
    p2.display("point de rotation");
    //Point::distance(p1, p2);
    //p1.distanceFromZero();

    p1.display("point avant rotation");
    p1.rotate(p2, -3.14*4/4);
    p1.display("point aprés rotation" );

    qDebug()<<cos(3.14/4)<<endl;
    */

        if (xOk && yOk) {
            qDebug() << "Nouvelles coordonnées : X =" << xValue << ", Y =" << yValue;
            Chariot monChariot(maConfig); // Instancier l'objet chariot
            float angle = monChariot.calculAngleEquilibre(xValue, yValue);

            // Mise à jour des coordonnées dans la vue graphique
            this->m_graphique->setPointA(monChariot._PA._x, monChariot._PA._y);
            this->m_graphique->setPointB(monChariot._PB._x, monChariot._PB._y);qDebug() << "Mise à jour de l'angle =" << angle * 180 / 3.14;
            this->m_graphique->setPen1(monChariot._PC._x, monChariot._PC._y, angle * 180 / 3.14);

            //qDebug() << "Mise à jour de l'angle =" << angle * 180 / 3.14;
        } else {
            qDebug() << "Entrée invalide pour X ou Y.";
        }
    });

    /*
    Chariot monChariot(maConfig);
    float monAngle;
    monAngle = monChariot.calculAngleEquilibre(542, 430);
    this->m_graphique->setPointA(monChariot._PA._x, monChariot._PA._y);
    this->m_graphique->setPointB(monChariot._PB._x, monChariot._PB._y);
    //this->m_graphique->setPointA(0,400);
    this->m_graphique->setPen1(monChariot._PC._x, monChariot._PC._y, monAngle*180/3.14);
    qDebug()<<"point A x="<<monChariot._PA._x<<"  "<<"point A y="<<monChariot._PA._y;
    qDebug()<<"point B x="<<monChariot._PB._x<<"  "<<"point B y="<<monChariot._PB._y;
    qDebug()<<"Pen 1 x="<<monChariot._PC._x+35<<"  "<<"Pen 1 y="<<monChariot._PC._y; //decalage visuel
    qDebug()<<"Pen 2 x="<<monChariot._PC._x-35<<"  "<<"Pen 2 y="<<monChariot._PC._y+10;
    qDebug()<<"angle = "<<monAngle*180/3.14;
*/

/*
    Point p0(900,0);
    Point p1(600,0);
    Point p2(600,300);
    Ligne l1(p0,p1);
    Ligne l2(p0,p2);
    l1.display();
    l2.display();
    //qDebug()<<"valeur"<<Ligne::angleBetweenTo(l1,l2)*180/3.14<<endl;
    qDebug() << "valeur" << Ligne::angleBetweenTo(l1, l2) * 180 / 3.14;
*/


}
void Widget::onEnvoyerGCode() {
    gcode.envoyerGCode(scene->getTrajectoire());
}

Widget::~Widget()
{

    delete ui;
}

void Widget::onTextChanged(const QString &text) {
    // Créer une copie mutable de 'text'
    QString modifiedText = text;
    modifiedText.replace(",", "."); // Remplacer la virgule par un point

    // Mettre à jour le texte dans le QLineEdit
    lineEdit->setText(modifiedText);
}

double Widget::getSaisie() const
{
    return saisie; // Retourne la valeur saisie
}


// Slot pour récupérer la valeur du QLineEdit
void Widget::onButtonClicked()
{
    bool ok;
    double value = lineEdit->text().toDouble(&ok); // Récupère la valeur
    if (ok) {
        qDebug() << "Valeur saisie : " << value;
    } else {
        qDebug() << "Entrée invalide.";
    }
}

