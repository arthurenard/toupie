#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <iostream>
#include <deque>

#include "bases/Vecteur.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

class Memoire {
    public:
        //constructeur
        Memoire (std::deque<Vecteur> Tableau = {});

        //methodes
        void add_vect (Vecteur); //rajoute un vect à Tableau si Tableau.size < taille, modifie Tableau[curseur] si non
        Vecteur get_vect(size_t); //retourne Tableau[i % taille_max]
        size_t taille() const;

    protected:
        const size_t taille_max = 1500;
        std::deque<Vecteur> Tableau;
};

#endif
