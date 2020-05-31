#ifndef CONIQUEENERGETIQUE_H
#define CONIQUEENERGETIQUE_H

#include <iostream>
#include "Cone.h"
#include "bases/constantes.h"

class ConiqueEnergetique : public Cone {
    public:
    //constructeur
    ConiqueEnergetique (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon, bool move = false);

    //destructeur
    ~ConiqueEnergetique()=default;

    //methodes
    int getType() const override; //retourne un nombre representant la toupie energetique
    Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) const override;


    private:
        //attributs
        double delta_T = 0.00001;

        //methodes
        size_t degre_eqEvol () const override;
        double V (double theta) const;
        double H (double theta) const;

        double EnergiePotentielleInitiale;
        double EnergieTotaleInitiale;
        double MomentCinAzInitial;
        double VectRot3Initiale; 
};

int signe(double); //retourne + ou - 1 en fct du signe de l'entrée

#endif
