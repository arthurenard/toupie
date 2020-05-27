#include "ToupieG_Conique.h"

ToupieG_Conique::ToupieG_Conique(std::vector<Vecteur> p, double mV, double h, double r) :
    Cone (p, degre(), mV, h, r)
{}


Vecteur ToupieG_Conique::eq_evolution (std::vector<Vecteur>, double) {
    Vecteur retour(0, vect_rot_P_Rg()[1], vect_rot_P_Rg()[2], 0, 0);

    if (THETA >= epsilon) {
        retour[0] += ((vect_rot_P_Rg()[1] - (PSI_P * THETA_P * cos(THETA))) / sin(THETA));
        retour[2] += (((PSI_P * THETA_P) - (vect_rot_P_Rg()[1] * cos(THETA))) / sin(THETA));
    }
    return retour;
}

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

size_t ToupieG_Conique::degre () const {
    return 2;
}
