#include "ConiqueEnergetique.h"

ConiqueEnergetique::ConiqueEnergetique (std::vector<Vecteur> p, double mV, double h, double r, bool move) :
    Cone (p, degre(), mV, h, r, move)//, theta_P(0.)
{

}

Vecteur ConiqueEnergetique::eq_evolution (std::vector<Vecteur> p, double) {
    if (p.size() != degre()) throw Erreur("ConiqueEnergetique eq evol");
    Vecteur retour(5);
    double theta = p[0][1];

    retour[0] = H(theta);
    retour[2] = vect_rot_Rg()[2] - (cos(theta) * H (theta));
    if (V(theta) <= 2 * energie_totale()) {
        retour[1] = signe(theta_P) * sqrt(((2 * energie_totale()) - V(theta)) / (I1() + (masse() * d() *d())));
        if (signe(theta_P) != signe(retour[1])) theta_P *= -1;
    }
    else {
        theta_P *= -1;
        while (V(theta) > 2 * energie_totale()) {
            theta += theta_P * delta_T;
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
