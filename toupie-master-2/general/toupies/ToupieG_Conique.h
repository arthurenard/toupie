#ifndef TOUPIEG_CONIQUE_H
#define TOUPIEG_CONIQUE_H

#include <iostream>
#include "ConeSimple.h"
#include "bases/constantes.h"

class ToupieG_Conique : public ConeSimple {
    public:
        virtual Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;

    protected:
        Vecteur MA_Rg () const; //retourne le moment de force en A exprimé dans Rg
        Vecteur vect_rot_P_Rg () const; //retourne la derivée du vecteur rotation dans Rg
        Matrice33 IA_Rg () const; //retourne la matrice d'inertie en A exprimée dans Rg
        Matrice33 IA_P_Rg () const; //retourne la "dérivée" de la matrice IA dans Rg
    private:
        size_t degre () const override;
};

#endif
