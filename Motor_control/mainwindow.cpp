#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Populer les ComboBox de direction
    QStringList directions = {"Horaire", "Anti-horaire"};
    ui->directionComboBox1->addItems(directions);
    ui->directionComboBox2->addItems(directions);
    ui->directionComboBox3->addItems(directions);

    // Configurer le port série
    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyASM0"); // Changez selon votre port
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::WriteOnly);

    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::sendCommand);

    // Connexion pour mettre à jour le QLabel avec la valeur du slider
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow:: updateSpeedLabel);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::sendCommand()
{
    QString cmd;

    // Motor 1
    int steps1 = ui->stepSpinBox1->value();
    QString dir1 = (ui->directionComboBox1->currentIndex() == 0) ? "H" : "A";
    cmd += QString("M1:%1:%2;").arg(steps1).arg(dir1);

    // Motor 2
    int steps2 = ui->stepSpinBox2->value();
    QString dir2 = (ui->directionComboBox2->currentIndex() == 0) ? "H" : "A";
    cmd += QString("M2:%1:%2;").arg(steps2).arg(dir2);

    // Motor 3
    int steps3 = ui->stepSpinBox3->value();
    QString dir3 = (ui->directionComboBox3->currentIndex() == 0) ? "H" : "A";
    cmd += QString("M3:%1:%2;").arg(steps3).arg(dir3);

    // Speed
    int speed = ui->speedSlider->value();
    cmd += QString("V:%1;").arg(speed);

    serial->write(cmd.toUtf8());
}

// Slot pour mettre à jour le texte du QLabel avec la vitesse choisie
void MainWindow::updateSpeedLabel(int value)
{
    ui->speedLabel->setText(QString("Vitesse: %1").arg(value));
}
