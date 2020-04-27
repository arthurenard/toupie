#include "Toupie.h"

//constructeurs
Toupie::Toupie (Vecteur v, Vecteur w) :
	vect_P(v),
	vect_dP(w)
{}

Toupie::Toupie (std::vector<double> v, std::vector<double> w) :
	vect_P(v),
	vect_dP(w)
{}


//methodes publiques
Vecteur Toupie::eq_evolution (Vecteur P, Vecteur dP, double temps) {
	return -vect_P; //a modifier par la suite
}


void Toupie::EulerCromer (double dt, double temps) {
	vect_dP += dt * eq_evolution(vect_P, vect_dP, temps);
	vect_P += dt * vect_dP;
}


void Toupie::Newmark (double dt, double temps) {
	Vecteur s (eq_evolution(vect_P, vect_dP, temps));
	Vecteur r (eq_evolution(vect_P, vect_dP, temps));
	Vecteur q = vect_P;
	while ((vect_P - q).norme() >= epsilon) {
		q = vect_P;
		r = eq_evolution(vect_P, vect_dP, temps);
		vect_dP += (dt * (r +s)) * 0.5;
		vect_P += (dt * vect_dP) + (dt * dt * (r + (2*s)) * (1/6));
	}
}

void Toupie::RungeKutta (double dt, double temps) {
	Vecteur k1 (vect_dP);
	Vecteur k1b (eq_evolution(vect_P, vect_dP, temps));
	Vecteur k2 (vect_dP + ((dt/2) * k1b));
    Vecteur k2b	(eq_evolution (vect_P + ((dt/2) * k1), vect_dP + ((dt/2) * k1b), temps + dt/2));
	Vecteur k3 (vect_dP + ((dt/2) * k2b));
	Vecteur k3b (eq_evolution (vect_P + ((dt/2) * k2), vect_dP + ((dt/2) * k2b), temps + dt/2));
	Vecteur k4 (vect_dP + (dt * k3b));
	Vecteur k4b	(eq_evolution (vect_P + (dt * k3), vect_dP + (dt * k3b), temps));
	
	vect_P += ((dt/6) * (k1 + (2*k2) + (2*k3) + k4));
	vect_dP += ((dt/6) * (k1b + (2*k2b) + (2*k3b) + k4b));
}

//methodes protegees

//methodes inutiles aux beneficiaires
void Toupie::affiche (std::ostream &flux) const {
	std::cout << "P: " << vect_P << "\n" << "dP: " << vect_dP << "\n";
}


//operateurs externes
std::ostream& operator<<(std::ostream& flux, Toupie const& t) {
	t.affiche(flux);
	return flux;
}
