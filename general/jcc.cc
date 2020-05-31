#include "jcc.h"

JCC::JCC()
    :Balle(std::vector<Vecteur>{Vecteur(0,0,2.), Vecteur(0,0,0)}, 0,0,0)
{
    coefRest = 1.03;
}
Vecteur JCC::eq_evolution(std::vector<Vecteur>, double) const {
    return 1.3*vecteur_g;
}
