#include "Memoire.h"

Memoire::Memoire(std::deque<Vecteur> tab)
{
    for (size_t i(0); i < min (taille_max, tab.size()); i++) {
        if (Tableau[i].size() != 3) throw "dimension Memoire 1";
        Tableau.push_back(tab[i]);
    }
}

void Memoire::add_vect(Vecteur v) {
    if (v.size() != 3) throw "dimension Memoire 2";
    if (Tableau.size() >= taille_max) {
        Tableau.pop_back();
    }
    Tableau.push_back(v);
}

Vecteur Memoire::get_vect(size_t i) {
    return Tableau[i % taille_max];
}

