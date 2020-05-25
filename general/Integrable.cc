#include "Integrable.h"

//constructeurs
Integrable::Integrable (Vecteur v, Vecteur w) :
	vect_P(v),
	vect_dP(w)
{}

Integrable::Integrable (std::vector<double> v, std::vector<double> w) :
	vect_P(v),
	vect_dP(w)
{}


//methodes publiques
const Vecteur Integrable::get_vect_P (){
	return vect_P;
}

void Integrable::EulerCromer (double dt, double temps) {
    vect_dP += dt * eq_evolution (vect_P, vect_dP, temps);
	vect_P += dt * vect_dP;
}


void Integrable::Newmark (double dt, double temps) {
    double T0 = temps;
    double T1 = dt + T0;
    Vecteur P0 = vect_P;
    Vecteur P1 = P0;
    Vecteur dP0 = vect_dP;
    Vecteur dP1 = dP0;
    Vecteur s = eq_evolution(P0, dP0, T0);
    Vecteur q, r;

    do {
        q = P1;
        r = eq_evolution(P1, dP1, T1);
        dP1 = dP0 + (0.5 * dt * (r + s));
        P1 = P0 + (dt * dP0) + ((1./3.) * dt * dt * ((0.5 * r) + s));
    } while ((P1 - q).norme() >= epsilon);

    vect_P = P1;
    vect_dP = dP1;
}

void Integrable::RungeKutta (double dt, double temps) {
	Vecteur k1 (vect_dP);
	Vecteur k1b (eq_evolution(vect_P, vect_dP, temps));
	Vecteur k2 (vect_dP + ((dt/2) * k1b));
    Vecteur k2b (eq_evolution (vect_P + ((dt/2) * k1), vect_dP + ((dt/2) * k1b), temps + dt/2));
	Vecteur k3 (vect_dP + ((dt/2) * k2b));
	Vecteur k3b (eq_evolution (vect_P + ((dt/2) * k2), vect_dP + ((dt/2) * k2b), temps + dt/2));
	Vecteur k4 (vect_dP + (dt * k3b));
    Vecteur k4b (eq_evolution (vect_P + (dt * k3), vect_dP + (dt * k3b), temps));
	
  	vect_P += ((dt/6) * (k1 + (2*k2) + (2*k3) + k4));
	vect_dP += ((dt/6) * (k1b + (2*k2b) + (2*k3b) + k4b));
}

//methodes protegees

//methodes inutiles aux beneficiaires
void Integrable::affiche (std::ostream &flux) const {
	std::cout << "P: " << vect_P << "\n" << "dP: " << vect_dP << "\n";
}


//operateurs externes
std::ostream& operator<<(std::ostream& flux, Integrable const& t) {
	t.affiche(flux);
	return flux;
}
