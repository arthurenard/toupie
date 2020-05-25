#include "ToupieChinoise.h"

//constructeurs

ToupieChinoise::ToupieChinoise (Vecteur vect_P, Vecteur vect_dP, double mV, double h, double r) :
        Toupie (vect_P, vect_dP, abs(mV), abs(h), abs(r))
{}

ToupieChinoise::ToupieChinoise (std::vector<double> vect_P, std::vector<double> vect_dP, double mV, double h, double r) :
        Toupie (vect_P, vect_dP, abs(mV), abs(h), abs(r))
{}

//destructeurs

//methodes publiques
Vecteur ToupieChinoise::eq_evolution (Vecteur P, Vecteur dP, double temps) {
	double r (rayon), m(masse());
    	Vecteur retour (5);
    	double f1 (dP[2] + (dP[0] * cos(P[1])));
    	double f3 ((I1() * I3()) + (masse() * I1() * pow(sin(P[1]) * r, 2)) + (masse() * I3() * pow(r * (alpha() - cos(P[1])), 2)));
    	double f2 ((dP[1] * f1 * I3() * (I3() + (m * r * r * (1 - (alpha() * cos(P[1])))))/(f3 * sin(P[1]))) - (2 * dP[0] * dP[1] / tan(P[1])));
	
	
        retour[0] = f2;
	
    	retour[1] =  sin(P[1]) * (dP[0] * dP[0] * (-m * r * r * (alpha() - cos(P[1])) * (1 - (alpha() * cos(P[1]))) + (I1() * cos(P[1]))) +
    (f1 * dP[0] * (m * r * r * ((alpha() * cos(P[1])) - 1) - I3())) - ((m * r * r * alpha() * pow(dP[1], 2))  - (m * g * r * alpha())))
    / (I1() + (m * r * r * (pow(alpha() - cos(P[1]), 2) + pow(sin(P[1]), 2))));
	
    	retour[2] = (dP[0] * dP[1] * sin(P[1])) - (cos(P[1]) * f2)
    - (m * pow(r, 2) * f1 * dP[1] * sin(P[1]) * ((I3() * (alpha() - cos(P[1]))) + (I1() * cos(P[1]))))/f3;
	
        retour[3] = r * ( (dP[1] * sin(P[0]) ) - (vect_dP[2] * cos(P[0]) * sin(P[1])));
        retour[4] = - r * (dP[1] * cos(P[0]) + (vect_dP[2] * sin(P[0]) * sin(P[1])));
	
	return retour;
}

//methodes protegees
double ToupieChinoise::volume () const {
	double r (rayon), h (hauteur);
	return pi * (((4.0/3) * pow(r, 3)) - (pow(h, 2) * (r - ((1.0/3) * h)))); // p9
}

double ToupieChinoise::alpha() const {
	double r (rayon), h (hauteur);
	return (0.75 * h * h) / ((r + h) * r);
}

double ToupieChinoise::I1 () const {
	double r (rayon), h (hauteur);
    	return (0.5 * I3()) + (pi * (1.0/15.) * masseVolumique * pow((2*r) - h, 2) * (pow(r, 3) + (h*r*r) - (3*h*h*r) + 3 * pow(h, 3))) - (masse() * pow(r * alpha(), 2)); // p9
}

double ToupieChinoise::I3 () const {
	double r (rayon), h (hauteur);
    	return pi * (1.0/30.) * masseVolumique * pow((2*r) - h, 3) * (2 * pow(r, 2) + (3 * h * r) + (3 * pow(h, 2))); // p9
}

Vecteur ToupieChinoise::OG () const {
    	return (rayon * OG_unitaire());
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe


//operateurs externes
