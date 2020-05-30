#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <iostream>
#include <deque>

#include "Erreur.h"
#include "bases/Vecteur.h"


class Memoire {
    public:
        //constructeur
        Memoire (std::deque<Vecteur> Tableau = {});

        //methodes
        void add_vect (Vecteur); //permet de rajouter un Vecteur
        Vecteur get_vect(size_t) const; //retourne Tableau[i % taille_max]
        size_t taille() const; //renvoie la taille de la Mémoire
        void clear(); //vide le Tableau

    protected:
        const size_t taille_max = 1500;
        std::deque<Vecteur> Tableau;
};

#endif
