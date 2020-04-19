#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QApplication>
#include "planete.h"
#include <vector>
#include <QWidget>
#include <QtWidgets>
#include "glwidget.h"
#include <QSound>



class Configuration : public QWidget
{
Q_OBJECT
public:
    Configuration();
    ~Configuration();
    //void startSimulation(){simulation->show();}

public slots:
    void actualiser();

private:
    std::vector<Planete*> systeme;

    QGridLayout* fenetre;

    std::vector<QGroupBox*> planete;
    std::vector<QLineEdit*> masses;
    std::vector<QLineEdit*> tailles;
    std::vector<QLineEdit*> coordsX;
    std::vector<QLineEdit*> coordsY;
    std::vector<QLineEdit*> vitsX;
    std::vector<QLineEdit*> vitsY;

    void addPlanete(size_t nb);



    QPushButton *bouton;
    GLWidget *simulation;
    QSound *HyperVitesse;
    QSpinBox *nbPlanete;



};

#endif // CONFIGURATION_H
