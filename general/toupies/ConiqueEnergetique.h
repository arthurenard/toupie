#ifndef CONIQUEENERGETIQUE_H
#define CONIQUEENERGETIQUE_H

#include <iostream>
#include "ConeSimple.h"
#include "bases/constantes.h"

class ConiqueEnergetique : public ConeSimple {
    public:
    Vecteur eq_evolution (Vecteur P = 0, double temps = 0); // a regler histoire que ça marche bien

    protected:
        double theta_P;
        double delta_T = 0.0001;
        double V (double theta) const;
        double H (double theta) const;
};

int signe(double); //retourne + ou - 1 en fct du signe de l'entrée

#endif
