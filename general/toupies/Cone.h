#ifndef CONE_H
#define CONE_H

#include <iostream>
#include "Toupie.h"
#include "bases/constantes.h"

class Cone : public Toupie {
    public:
        //constructeur
        Cone(std::vector<Vecteur> position, double masseVolumique, double hauteur, double rayon, bool move = false);

        //destructeur
        virtual ~Cone()=default;


    protected:
        //attributs

        //methodes protégées
            double volume () const override; // m3, volume d'un cone calculé avec le rayon et la hauteur
            double I1 () const override; // kg * m2, composante de la matrice diagonale d'inertie de G dans Rg, I1 = I2
            double I3 () const override; // kg * m2, composante de la matrice diagonale d'inertie de G dans Rg
            double IA1 () const; // kg * m2, composante de la matrice d'inertie de A dans Rg
            double MA () const; //renvoie le moment de force en A (le poids est l'unique force)
            double d () const; //retourne ||OG|| (=3/4 de la hauteur pour un cone)

            Vecteur OG() const override; //renvoie le vecteur OG dans la base Ro (vecteur entre le point de contact et le centre de gravité)
};

#endif // CONE_H
