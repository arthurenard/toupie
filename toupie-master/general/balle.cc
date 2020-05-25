#include "balle.h"

Balle::Balle(Vecteur P, Vecteur dP, double r, double v, double b): Integrable(P, dP), rayon(0.1), coefRest(1.0)
{
    rvb.push_back(r);
    rvb.push_back(v);
    rvb.push_back(b);
}

Vecteur Balle::eq_evolution (Vecteur P, Vecteur dP, double temps) {
    return vecteur_g;
}

void Balle::EulerCromer(double pas_de_temps, double temps){
    Integrable::EulerCromer(pas_de_temps, temps);
    if(vect_P[2] - rayon< 0 ){
        vect_dP[2]*= -coefRest;
        vect_P[2]=rayon;
    }
}
