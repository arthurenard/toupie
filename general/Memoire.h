#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <iostream>
#include <deque>

#include "bases/Vecteur.h"

//#define min(a, b) ((a) < (b) ? (a) : (b))

class Memoire {
    public:
        //constructeur
        Memoire (std::deque<Vecteur> Tableau = {});

        //methodes
        void add_vect (Vecteur);
        Vecteur get_vect(size_t); //retourne Tableau[i % taille_max]
        size_t taille() const;
        void clear(){Tableau.clear();}

    protected:
        const size_t taille_max = 1500;
        std::deque<Vecteur> Tableau;
};

#endif
