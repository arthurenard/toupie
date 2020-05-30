#include "ToupieG_Conique.h"
//constructeur
ToupieG_Conique::ToupieG_Conique(std::vector<Vecteur> p, double mV, double h, double r, bool move) :
    Cone (p, mV, h, r, move)
{}

//methodes
Vecteur ToupieG_Conique::eq_evolution (std::vector<Vecteur> p, double) const {
    if (p.size() != degre_Position()) throw Erreur("ToupieG_Conique eq evol");
    Vecteur retour(0, vect_rot_P_Rg()[0], vect_rot_P_Rg()[2], 0, 0);
    double theta(p[0][1]), psi_P(p[1][0]), theta_P(p[1][1]);

    if (abs(theta) >= epsilon) {
        retour[0] += ((vect_rot_P_Rg()[1] - (psi_P * theta_P * cos(theta))) / sin(theta));
        retour[2] += (((psi_P * theta_P) - (vect_rot_P_Rg()[1] * cos(theta))) / sin(theta));
    }
    return retour;
}

//methodes privées
Vecteur ToupieG_Conique::MA_Rg() const {
    return Vecteur(MA (), 0, 0);
}

Vecteur ToupieG_Conique::vect_rot_P_Rg () const {
    return (IA_Rg().inv() * (MA_Rg () - (vect_rotDeRg_Rg() ^ (IA_Rg() * vect_rot_Rg())) - (IA_P_Rg() * vect_rot_Rg())));
}

Matrice33 ToupieG_Conique::IA_Rg() const {
    Matrice33 m (OG().norme2(), OG().norme2(), 0);
    return (inertie() + (masse() * m));
}

Matrice33 ToupieG_Conique::IA_P_Rg() const {
    return Matrice33(0, 0, 0);
}

int ToupieG_Conique::getType () const{
    return CONIQUEG;
}

size_t ToupieG_Conique::degre_eqEvol() const {
    return 2;
}
