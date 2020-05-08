#include "ConeSimple.h"

//constructeurs
ConeSimple::ConeSimple() :
    Toupie(),
    masseVolumique(1.0),
    hauteur(1.0),
    rayon(1.0)
{}


ConeSimple::ConeSimple (Vecteur vect_P, Vecteur vect_dP, double mV, double h, double r) :
	Toupie (vect_P, vect_dP),
	masseVolumique (abs(mV)),
	hauteur (abs(h)),
	rayon (abs(r))
{}

ConeSimple::ConeSimple (std::vector<double> vect_P, std::vector<double> vect_dP, double mV, double h, double r) : 
	Toupie (vect_P, vect_dP),
	masseVolumique (abs(mV)),
	hauteur (abs(h)),
	rayon (abs(r))
{}

//destructeurs

//methodes publiques

Vecteur ConeSimple::eq_evolution (Vecteur P, Vecteur dP, double temps) {
    Vecteur retour (5);
    retour[1] = (1/IA1() ) * (MA() + (vect_dP[0] * sin(vect_P[1]) * ( ( (IA1() - I3()) * vect_dP[0] * cos(vect_P[1])) - (I3() * vect_dP[2]))));

    if(abs(vect_P[1]) < epsilontheta){
        retour[0]=0.0;
        retour[2]=0.0;
        return retour;
    }

    retour[0] = (vect_dP[1] / (IA1() * sin(vect_P[1]))) * (((I3() - (2 * IA1())) * vect_dP[0] * cos(vect_P[1])) + (I3() * vect_dP[2]));
    retour[2] = (vect_dP[1] / (IA1() * sin(vect_P[1]))) * ( ( ( vect_dP[0] * ( IA1() - ( ( I3() - IA1() ) * cos(vect_P[1]) * cos(vect_P[1]))) - ( I3() *vect_dP[2] * cos(vect_P[1])))));
	return retour;
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe

//methodes protegees
double ConeSimple::volume () const {
	return ((pi * rayon * rayon * hauteur) / 3);
}

double ConeSimple::I1 () const {
    return (3./20.) * masse() * ((rayon * rayon) + (0.25 * hauteur * hauteur));
}

double ConeSimple::I3 () const {
    return (3./10.) * masse() * rayon * rayon;
}

double ConeSimple::IA1 () const {
    return (I1() + ((9./16.) * hauteur * hauteur));
}

double ConeSimple::MA () const {
	return (masse () * g * hauteur * sin(vect_P[1]));  // cas ou la toupie n'est soumise qu'a son seul poids
}

Vecteur ConeSimple::OG() const {
    return (0.75 * hauteur * OG_unitaire());
}

//operateurs externes


