#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configure serial port
    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyACM0"); // Change as per your port
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::WriteOnly);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::sendCommand);

    // Connect direction buttons
    connect(ui->buttonUp, &QPushButton::clicked, this, &MainWindow::setDirectionUp);
    connect(ui->buttonDown, &QPushButton::clicked, this, &MainWindow::setDirectionDown);
    connect(ui->buttonLeft, &QPushButton::clicked, this, &MainWindow::setDirectionLeft);
    connect(ui->buttonRight, &QPushButton::clicked, this, &MainWindow::setDirectionRight);

    // Update speed label when slider is moved
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::updateSpeedLabel);

    // Default directions
    motor1Direction = "H";
    motor2Direction = "H";
    motor3Direction = "H";

    // Default pull states
    pull1 = "PA10_H";
    pull2 = "PB5_H";
    pullPen = "PA15_H";
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::setDirectionUp()
{
    motor1Direction = "PB10_H";
    motor2Direction = "PB7_H";
    motor3Direction = "PB4_H";
}

void MainWindow::setDirectionDown()
{
    motor1Direction = "PB10_A";
    motor2Direction = "PB7_A";
    motor3Direction = "PB4_A";
}

void MainWindow::setDirectionLeft()
{
    motor1Direction = "PB10_A";
    motor2Direction = "PB7_H";
    motor3Direction = "PB4_H";
}

void MainWindow::setDirectionRight()
{
    motor1Direction = "PB10_H";
    motor2Direction = "PB7_A";
    motor3Direction = "PB4_H";
}

void MainWindow::sendCommand()
{
    QString cmd;

    // Motor 1 (PB10)
    int steps1 = ui->stepSpinBox1->value();
    cmd += QString("M1:%1:%2;").arg(steps1).arg(motor1Direction);

    // Motor 2 (PB7)
    int steps2 = ui->stepSpinBox2->value();
    cmd += QString("M2:%1:%2;").arg(steps2).arg(motor2Direction);

    // Motor 3 (PB4)
    int steps3 = ui->stepSpinBox3->value();
    cmd += QString("M3:%1:%2;").arg(steps3).arg(motor3Direction);

    // Speed
    int speed = ui->speedSlider->value();
    cmd += QString("V:%1;").arg(speed);

    // Pull states
    cmd += QString("P1:%1;").arg(pull1);
    cmd += QString("P2:%1;").arg(pull2);
    cmd += QString("PP:%1;").arg(pullPen);

    serial->write(cmd.toUtf8());
}

void MainWindow::updateSpeedLabel()
{
    int speed = ui->speedSlider->value();
    ui->speedLabel->setText(QString("Speed: %1").arg(speed));
}
