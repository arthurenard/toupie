#include "Toupie.h"

//methodes
Vecteur Toupie::eq_evolution (unsigned long long int t, Vecteur vect_P, Vecteur vect_dP) {
	return -vect_P; //a modifier par la suite
}

//methodes inutiles aux beneficiaires
void Toupie::affiche (std::ostream &flux) const {
	std::cout << vect_P << "\n" << "dP: " << vect_dP << "\n";
}

//operateurs externes
std::ostream& operator<<(std::ostream& flux, Toupie const& t) {
	t.affiche(flux);
	return flux;
}
