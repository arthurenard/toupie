#include "Toupie.h"

//constructeurs
Toupie::Toupie (Vecteur v, Vecteur w) {
	if (v.size() == 3) {
        v.push_back(0.);
        v.push_back(0.);
	}
    if (v.size() != 5) throw "Vecteur Toupie";

     Integrable::vect_P=v;
	
	if (w.size() == 3) {
        w.push_back(0.);
        w.push_back(0.);
	}
    if (w.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_dP = w;
}

Toupie::Toupie (std::vector<double> v, std::vector<double> w)
{
	if (v.size() == 3) {
        v.push_back(0.);
        v.push_back(0.);
	}
    if (v.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_P = v;

	if (w.size() == 3) {
        w.push_back(0.);
        w.push_back(0.);
	}
    if (w.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_dP = w;
}


void Toupie::EulerCromer(double pas_de_temps, double temps) {
    Integrable::EulerCromer(pas_de_temps, temps);
    modulo2pi();
}
void Toupie::RungeKutta(double pas_de_temps, double temps) {
    Integrable::RungeKutta(pas_de_temps, temps);
    modulo2pi();
}

void Toupie::Newmark(double pas_de_temps, double temps) {
    Integrable::Newmark(pas_de_temps, temps);
    modulo2pi();
}

void Toupie::modulo2pi(){
    Integrable::vect_P[0] = fmod(Integrable::vect_P[0], 2*pi);
    Integrable::vect_P[1] = fmod(Integrable::vect_P[1], 2*pi);
    Integrable::vect_P[2] = fmod(Integrable::vect_P[2], 2*pi);
}
