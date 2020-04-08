#include "ToupieChinoise.h"

//constructeurs

ToupieChinoise::ToupieChinoise (Vecteur vect_P, Vecteur vect_dP, double mV, double r, double h) :
	Toupie (vect_P, vect_dP),
	masseVolumique (abs(mV)),
	rayon (abs(r)),
	hauteur (abs(h))
{}

ToupieChinoise::ToupieChinoise (std::vector<double> vect_P, std::vector<double> vect_dP, double mV, double r, double h) : 
	Toupie (vect_P, vect_dP),
	masseVolumique (abs(mV)),
	rayon (abs(r)),
	hauteur (abs(h))
{}

//destructeurs

//methodes publiques
Vecteur ToupieChinoise::eq_evolution (Vecteur P, Vecteur dP, double temps) {
	double r (rayon), m(masse());
	Vecteur retour (3);
	double f1 (vect_dP[2] + cos(vect_P[1]));
	double f3 ((I1() * I3()) + (masse() * I1() * pow(sin(vect_P[1]) * r, 2)) + (masse() * I3() * pow(r * (alpha() - cos(vect_P[1])), 2)));
	double f2 ((vect_dP[1] * f1 * I3() * (I3() + (m * r * r * (1 - (alpha() * cos(vect_P[1])))))/(f3 * sin(vect_P[1]))) - (2 * vect_dP[0] * vect_dP[1] / tan(vect_P[0])));
	
	
	retour[0] = f2;
	
	retour[1] =  sin(vect_P[1]) * (vect_dP[0] * vect_dP[0] * (-m * r * r * (alpha() - cos(vect_P[1])) * (1 - (alpha() * cos(vect_P[1]))) + (I1() * cos(vect_P[1]))) +
	(f1 * vect_dP[0] * (m * r * r * ((alpha() * cos(vect_P[0])) - 1)) - I3()) - ((m * r * alpha()) * ((r * pow(vect_dP[1], 2)) + (m * g))))
	/ (I1() + (m * r * r * (pow(alpha() - cos(vect_P[1]), 2) + pow(sin(vect_P[1]), 2))));
	
	retour[2] = (vect_dP[0] * vect_dP[1] * sin(vect_P[1])) - (cos(vect_P[1]) * f2) 
	- (m * pow(r, 2) * f1 * vect_dP[1] * sin(vect_P[1]) * ((I3() * (alpha() - cos(vect_P[1]))) + (I1() * cos(vect_P[1]))))/f3;
	
	return retour;
}

//methodes protegees
const double ToupieChinoise::volume () const {
	double r (rayon), h (hauteur);
	return pi * (((4/3) * pow(r, 3)) - (pow(h, 2) * (r - ((1/3) * h)))); // p9
}

const double ToupieChinoise::masse () const {
	return masseVolumique * volume();
}

const double ToupieChinoise::alpha() const {
	double r (rayon), h (hauteur);
	return (0.75 * h * h) / ((r + h) * r);
}

const double ToupieChinoise::I1 () const {
	double r (rayon), h (hauteur);
	return (0.5 * I3()) + (pi * (1/15) * masseVolumique * pow((2*r) - h, 2) * (pow(r, 3) + (h*r*r) - (3*h*h*r) + 3 * pow(h, 3))) - (masse() * pow(r * alpha(), 2)); // p9
}

const double ToupieChinoise::I3 () const {
	double r (rayon), h (hauteur);
	return pi * (1/30) * masseVolumique * pow((2*r) - h, 3) * (2 * pow(r, 2) + (3 * h * r) + (3 * pow(h, 2))); // p9
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe


//operateurs externes


