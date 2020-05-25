#include "ConeSimple.h"

//constructeurs
ConeSimple::ConeSimple() :
        Toupie()
{}


ConeSimple::ConeSimple (Vecteur vect_P, Vecteur vect_dP, double mV, double h, double r) :
        Toupie (vect_P, vect_dP, mV, abs(h), abs(r))

{}

ConeSimple::ConeSimple (std::vector<double> vect_P, std::vector<double> vect_dP, double mV, double h, double r) : 
        Toupie (vect_P, vect_dP, mV, abs(h), abs(r))

{}

//destructeurs

//methodes publiques

Vecteur ConeSimple::eq_evolution (Vecteur P, Vecteur dP, double temps) {
	Vecteur retour (5);

    	retour[1] = (1/IA1() ) * (MA() + (dP[0] * sin(P[1]) * ( ( (IA1() - I3()) * dP[0] * cos(P[1])) - (I3() * dP[2]))));

    	if(abs(P[1]) < epsilontheta){
        	retour[0]=0.0;
        	retour[2]=0.0;
        	return retour;
    	}

    	retour[0] = (P[1] / (IA1() * sin(P[1]))) * (((I3() - (2 * IA1())) * dP[0] * cos(P[1])) + (I3() * dP[2]));
        retour[2] = (dP[1] / (IA1() * sin(P[1]))) *  ( dP[0] * ( IA1() - ( ( I3() - IA1() ) * cos(P[1]) * cos(P[1]))) - ( I3() * dP[2] * cos(P[1])));


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
        return masse() * ((3./20.)*rayon*rayon + 0.6*hauteur*hauteur);
}

double ConeSimple::MA () const {
    return (d() * masse () * g * sin(THETA));  // cas ou la toupie n'est soumise qu'a son seul poids
}

double ConeSimple::d () const {
    return (0.75 * hauteur);
}

Vecteur ConeSimple::OG() const {
        return (d() * OG_unitaire());
}

//operateurs externes

