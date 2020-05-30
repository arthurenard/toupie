#include "ConiqueEnergetique.h"

//constructeur
ConiqueEnergetique::ConiqueEnergetique (std::vector<Vecteur> p, double mV, double h, double r, bool move) :
    Cone (p, mV, h, r, move),
    EnergiePotentielleInitiale(energie_pot()),
    EnergieTotaleInitiale(masse() * g * d() * cos(p[0][1]) + 0.5 * ((I1() + masse() *d() *d()) * (vect_rot_Rg()[0] + vect_rot_Rg()[1]) + I3()*vect_rot_Rg()[2]*vect_rot_Rg()[2])),
    MomentCinAzInitial(invariant_moment_cin_Az()),
    VectRot3Initiale(vect_rot_Rg()[2])
{}

//methodes
Vecteur ConiqueEnergetique::eq_evolution (std::vector<Vecteur> p, double) const {
    if (p.size() != degre_Position()) throw Erreur("ConiqueEnergetique eq evol");
    Vecteur retour(5);
    double theta(p[0][1]);

    retour[0] = H(theta);
    retour[2] = VectRot3Initiale - (cos(theta) * H (theta));
    if (V(theta) <= 2 * EnergieTotaleInitiale) {
        retour[1] = signe(p[1][1]) * sqrt(((2 * EnergieTotaleInitiale) - V(theta)) / (I1() + (masse() * d() *d())));
        if (signe(p[1][1]) != signe(retour[1])) p[1][1] *= -1;
    }
    else {
        p[1][1] *= -1;
        size_t compteur(0);
        while (V(theta) > 2 * EnergieTotaleInitiale) {
            theta += p[1][1] * delta_T;
            compteur++;
            if (compteur > 1000000) throw Erreur("Energetique boucle inf");
        }
        retour[1] = 0;
    }
    return retour;
}

//
//private
//

//methodes privées
double ConiqueEnergetique::V (double t) const {
    return ((I3() * VectRot3Initiale * VectRot3Initiale) + (2 * EnergiePotentielleInitiale) + ((I1() + masse() * d() * d()) * H(t) * H(t)));
}

double ConiqueEnergetique::H (double t) const {
    return ( (MomentCinAzInitial - (I3() * VectRot3Initiale * cos(t))) / ((I1() + (masse() * d() * d())) * sin(t) * sin(t)));
}

int signe(double x) {
    if (x<0) return -1;
    return 1;
}

int ConiqueEnergetique::getType() const {
    return CONIQUEE;
}

size_t ConiqueEnergetique::degre_eqEvol() const {
    return 1;
}
