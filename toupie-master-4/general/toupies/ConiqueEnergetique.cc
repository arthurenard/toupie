#include "ConiqueEnergetique.h"

ConiqueEnergetique::ConiqueEnergetique (std::vector<Vecteur> p, double mV, double h, double r) :
    Cone (p, degre(), mV, h, r)
{}

Vecteur ConiqueEnergetique::eq_evolution (std::vector<Vecteur>, double) {
    Vecteur retour(5);

    retour[0] = H(THETA);
    retour[2] = vect_rot_Rg()[2] - (cos(THETA) * H (THETA));
    if (V(THETA) <= 2 * energie_totale()) {
        retour[1] = signe(theta_P) * sqrt(((2 * energie_totale()) - V(THETA)) / (I1() + (masse() * d() *d())));
        if (signe(theta_P) != signe(retour[1])) theta_P *= -1;
    }
    else {
        theta_P *= -1;
        while (V(THETA) > 2 * energie_totale()) {
            THETA += theta_P * delta_T;
        } // retour[1] est de base = 0, inutile donc de le repréciser
    }
    return retour;
}

double ConiqueEnergetique::V (double t) const {
    return ((I3() * vect_rot_Rg()[2] * vect_rot_Rg()[2]) + (2 * energie_pot()) + ((I1() + masse() * d() * d()) * H(t)));
}

double ConiqueEnergetique::H (double t) const {
    return ( (invariant_moment_cin_Az() - (I3() * vect_rot_Rg()[2] * cos(t))) / ((I1() + (masse() * d() * d())) * sin(t) * sin(t)));
}

int signe(double x) {
    if (x<0) return -1;
    return 1;
}

size_t ConiqueEnergetique::degre () const {
    return 1;
}
