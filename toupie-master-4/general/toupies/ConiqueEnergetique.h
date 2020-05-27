#ifndef CONIQUEENERGETIQUE_H
#define CONIQUEENERGETIQUE_H

#include <iostream>
#include "Cone.h"
#include "bases/constantes.h"

class ConiqueEnergetique : public Cone {
    public:
    ConiqueEnergetique (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon);

    Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;

    protected:
        double theta_P;
        double delta_T = 0.0001;
        double V (double theta) const;
        double H (double theta) const;
    private:
        size_t degre () const override;
};

int signe(double); //retourne + ou - 1 en fct du signe de l'entrée

#endif
