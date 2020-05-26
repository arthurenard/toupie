#ifndef CONE_H
#define CONE_H

#include <iostream>
#include "Toupie.h"
#include "bases/constantes.h"

class Cone : public Toupie {
    public:
        Cone(std::vector<Vecteur> position, size_t degre, double masseVolumique, double hauteur, double rayon);

    protected:
        //attributs

        //methodes privees
            double volume () const override; // m3
            double I1 () const override; // kg * m2
            double I3 () const override; // kg * m2
            double IA1 () const; // kg * m2
            double MA () const;
            double d () const; //retourne ||OG|| (=3/4 de la hauteur)

            Vecteur OG() const override;
};

#endif
