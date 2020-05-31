#ifndef TOUPIEG_CONIQUE_H
#define TOUPIEG_CONIQUE_H

#include <iostream>
#include "Cone.h"
#include "bases/constantes.h"

class ToupieG_Conique : public Cone {
    public:
        //constructeurs
        ToupieG_Conique(std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon, bool move = false);

        //destructeur
        ~ToupieG_Conique()=default;

        //methodes
        virtual Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) const override;
        int getType() const override; //retourne un entier representant le type de la toupie


    private:
        //methodes
        Vecteur MA_Rg () const; //retourne le moment de force en A exprimé dans Rg
        Vecteur vect_rot_P_Rg () const; //retourne la derivée du vecteur rotation dans Rg
        Matrice33 IA_Rg () const; //retourne la matrice d'inertie en A exprimée dans Rg
        Matrice33 IA_P_Rg () const; //retourne la "dérivée" de la matrice IA dans Rg

        size_t degre_eqEvol () const override; //retourne le degre des equations d'evolution (ici 2)
};

#endif
