#ifndef CONIQUEENERGETIQUE_H
#define CONIQUEENERGETIQUE_H

#include <iostream>
#include "Cone.h"
#include "bases/constantes.h"

class ConiqueEnergetique : public Cone {
    public:
    ConiqueEnergetique (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon, bool move = false);

    Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;
    int getType() override;


    protected:
        double theta_P;
        double delta_T = 0.0001;
        double V (double theta) const;
        double H (double theta) const;
/*
        double EnergieTotaleInitiale;
        double MomentCinAzInitial;
        double VectRot3Initiale;
*/
    private:
        size_t degre_eqEvol () const override;
};

int signe(double); //retourne + ou - 1 en fct du signe de l'entrée

#endif
