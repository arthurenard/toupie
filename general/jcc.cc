#include "jcc.h"

JCC::JCC()
    :Balle(std::vector<Vecteur>{Vecteur(0,0,3.), Vecteur(0,0,0)}, 0,0,0)
{
}
Vecteur JCC::eq_evolution(std::vector<Vecteur>, double temps){
    return 0,2*vecteur_g;
}
