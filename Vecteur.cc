#include "Vecteur.h"

int main() {}

void Vecteur::augmente (double valeur) {
	vecteur.push_back(valeur);
}

void Vecteur::set_coord (size_t i, double valeur) {
	vecteur[i]=valeur;
}

void Vecteur::affiche (std::ostream &flux) const {
	std::cout << "(";
	for (size_t i(0); i < vecteur.size() ; i++) {
		std::cout << vecteur[i];
		if (i < vecteur.size()-1) std::cout << ", "; 
	}
	std::cout << ")";
}

Vecteur Vecteur::addition (Vecteur const& autre) const {
	if (autre.vecteur.size() != vecteur.size()) throw "addition";
	else {
		Vecteur retour; 
		for (size_t i(0) ; i < vecteur.size() ; i++) {
			retour.augmente(autre.vecteur[i]+vecteur[i]);
		}
		return retour;
	}
}

Vecteur Vecteur::oppose() const {
	Vecteur retour;
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour.augmente(-vecteur[i]);
	}
	return retour;
}

Vecteur Vecteur::soustraction (Vecteur const& autre) const {
	if (autre.vecteur.size() != vecteur.size()) throw "soustraction";
	else {
		Vecteur retour; 
		for (size_t i(0) ; i < vecteur.size() ; i++) {
			retour.augmente(-autre.vecteur[i]+vecteur[i]);
		}
		return retour;
	}
}

Vecteur Vecteur::mult (double scal) const {
	Vecteur retour;
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour.augmente(scal*vecteur[i]);
	}
	return retour;
}

double Vecteur::prod_scal (Vecteur const& autre) const {
	if (autre.vecteur.size() != vecteur.size()) throw "produit scal";
	else {
		double retour(0); 
		for (size_t i(0) ; i < vecteur.size() ; i++) {
			retour+=autre.vecteur[i]*vecteur[i];
		}
		return retour;
	}
}

Vecteur Vecteur::prod_vect (Vecteur const& autre) const {
	Vecteur retour; 
	retour.augmente(vecteur[1]*autre.vecteur[2]-vecteur[2]*autre.vecteur[1]);
	retour.augmente(vecteur[2]*autre.vecteur[0]-vecteur[0]*autre.vecteur[2]);
	retour.augmente(vecteur[0]*autre.vecteur[1]-vecteur[1]*autre.vecteur[0]);
	return retour;
}

double Vecteur::norme2 () const {
	double retour(0); 
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour+=vecteur[i]*vecteur[i];
	}
	return retour;
}

double Vecteur::norme () const {
	return sqrt(this->norme2());
}

Vecteur::Vecteur (size_t dim) {
	for (size_t i(0) ; i < dim ; i++) {
		this->augmente(0.0);
	}
}

Vecteur::Vecteur (double a, double b, double c) {
	this->augmente(a);
	this->augmente(b);
	this->augmente(c);
}

Vecteur::Vecteur (std::vector<double> liste) {
	for (size_t i(0) ; i < liste.size() ; i++) {
	this->augmente(liste[i]);
	}
}

bool Vecteur::operator== (Vecteur const& v) const {
	if (v.vecteur.size() != vecteur.size()) return false;
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		if (v.vecteur[i] != vecteur[i]) return false;
	}
	return true;
}

bool Vecteur::operator!= (Vecteur const& v) const {
	return !(*this == v);
}

std::ostream& operator<<(std::ostream& flux, Vecteur const& v) {
	v.affiche(flux);
	return flux;
}
