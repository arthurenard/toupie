#include "balle.h"

Balle::Balle(std::vector<Vecteur> p, double r, double v, double b) :
    Integrable(p, degre()),
    rayon(0.1),
    coefRest(1.0)
{
    rvb.push_back(r);
    rvb.push_back(v);
    rvb.push_back(b);
}

Vecteur Balle::eq_evolution (std::vector<Vecteur>, double) {
    return vecteur_g;
}

void Balle::EulerCromer(double pas_de_temps, double temps){
    Integrable::EulerCromer(pas_de_temps, temps);
    if (Position[0][2] - rayon< 0 ){
        Position[1][2]*= -coefRest;
        Position[0][2]=rayon;
    }
}

size_t Balle::degre () const {
    return 2;
}
