#include "Cone.h"

Cone::Cone(std::vector<Vecteur> p, size_t d, double mV, double h, double r, bool move) :
    Toupie(p, mV, h, r, move)
{}

//methodes protegees
double Cone::volume () const {
    return ((pi * rayon * rayon * hauteur) / 3);
}

double Cone::I1 () const {
        return (3./20.) * masse() * ((rayon * rayon) + (0.25 * hauteur * hauteur));
}

double Cone::I3 () const {
        return (3./10.) * masse() * rayon * rayon;
}

double Cone::IA1 () const {
        return masse() * ((3./20.)*rayon*rayon + 0.6*hauteur*hauteur);
}

double Cone::MA () const {
    return (d() * masse () * g * sin(THETA));  // cas ou la toupie n'est soumise qu'a son seul poids
}

double Cone::d () const {
    return (0.75 * hauteur);
}

Vecteur Cone::OG() const {
        return (d() * OG_unitaire());
}

