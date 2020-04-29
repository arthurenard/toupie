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
