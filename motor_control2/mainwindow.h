#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort> // Nécessaire pour QSerialPort

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setDirectionUp();
    void setDirectionDown();
    void setDirectionLeft();
    void setDirectionRight();
    void sendCommand();
    void updateSpeedLabel();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;  // Déclare un pointeur vers un objet QSerialPort

    // Directions pour chaque moteur
    QString motor1Direction;
    QString motor2Direction;
    QString motor3Direction;

    QString pull1;   // PA10
    QString pull2;   // PB5
    QString pullPen; // PA15
};

#endif // MAINWINDOW_H
