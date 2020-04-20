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
	Vecteur retour (3);
 	retour[0] = vect_dP[1] * (((I3() - (2 * IA1())) * vect_dP[0] * cos(vect_P[1])) - (I3() * vect_dP[2]));
	retour[1] = (1/IA1()) * (MA() + (vect_dP[0] * sin(vect_P[1]) * ( ( (IA1() - I3()) * vect_dP[0] * cos(vect_P[1])) - (I3() * vect_dP[2]))));
	retour[2] = (vect_dP[1] / (IA1() * sin(vect_P[1]))) * ( ( ( vect_dP[0] * ( IA1() - ( ( I3() - IA1() ) * cos(vect_P[1]) * cos(vect_P[1]))) - ( I3() *vect_dP[2] * cos(vect_P[1])))));
	return retour;
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe

//methodes protegees
const double ConeSimple::volume () const {
	return ((pi * rayon * rayon * hauteur) / 3);
}
 
const double ConeSimple::masse () const {
	return masseVolumique * volume();
}

const double ConeSimple::I1 () const {
	return (3/20) * masse() * ((rayon * rayon) + (0.25 * hauteur * hauteur));
}

const double ConeSimple::I3 () const {
	return (3/10) * masse() * rayon * rayon;
}

const double ConeSimple::IA1 () const {
	return (I1() + ((9/16) * hauteur * hauteur));
}

const double ConeSimple::MA () const {
	return (masse () * g * hauteur * sin(vect_P[1]));  // cas ou la toupie n'est soumise qu'a son seul poids
}

Vecteur ConeSimple::vect_rot () const {
	Vecteur retour (3);
	retour[0] = vect_dP[1];
	retour[1] = vect_dP[0] * sin(vect_P[1]);
	retour[2] = (vect_dP[0] * cos(vect_P[1])) + vect_dP[2];
	return retour;
}

//operateurs externes


