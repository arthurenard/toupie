#include "Vecteur.h"
//
//constructeurs
//

Vecteur::Vecteur (size_t dim) {
	for (size_t i(0) ; i < dim ; i++) {
		this->push_back(0.0);
	}
}

Vecteur::Vecteur (double a, double b, double c) {
	this->push_back(a);
	this->push_back(b);
	this->push_back(c);
}

Vecteur::Vecteur (double a, double b, double c, double d, double e) {
    this->push_back(a);
    this->push_back(b);
    this->push_back(c);
    this->push_back(d);
    this->push_back(e);
}
Vecteur::Vecteur (std::vector<double> liste) {
	for (size_t i(0) ; i < liste.size() ; i++) {
	this->push_back(liste[i]);
	}
}

//
//destructeur
//

//
//methodes
//

void Vecteur::push_back (double valeur) {
	vecteur.push_back(valeur);
}

size_t Vecteur::size() const {
	return vecteur.size();
}

double Vecteur::prod_scal (Vecteur const& autre) const {
    if (autre.vecteur.size() != vecteur.size()) throw Erreur("produit scal");
	else {
		double retour(0); 
		for (size_t i(0) ; i < vecteur.size() ; i++) {
			retour+=autre.vecteur[i]*vecteur[i];
		}
		return retour;
	}
}

double Vecteur::norme () const {
	return sqrt(this->norme2());
}

double Vecteur::norme2 () const {
	double retour(0); 
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour+=vecteur[i]*vecteur[i];
	}
	return retour;
}

Vecteur Vecteur::projection (Vecteur vect) const {
    return ((this->prod_scal(vect) /vect.norme2()) * vect);
}


//operateurs internes

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

const Vecteur Vecteur::operator- () const {
	Vecteur retour;
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour.push_back(-vecteur[i]);
	}
	return retour;
}
	
const Vecteur Vecteur::operator~ () const {
	Vecteur retour;
	double norme = this->norme();
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour.push_back(norme);
	}
	return retour;
}

const Vecteur Vecteur::operator+ (Vecteur const& autre) const {
    if (autre.vecteur.size() != vecteur.size()) throw Erreur("vecteur addition");
    Vecteur retour;
    for (size_t i(0) ; i < vecteur.size() ; i++) {
        retour.push_back(autre.vecteur[i]+vecteur[i]);
    }
    return retour;
}

const Vecteur Vecteur::operator- (Vecteur const& autre) const {
    if (autre.vecteur.size() != vecteur.size()) throw Erreur("vecteur soustraction");
    Vecteur retour;
    for (size_t i(0) ; i < vecteur.size() ; i++) {
        retour.push_back(-autre.vecteur[i]+vecteur[i]);
    }
    return retour;
}

const Vecteur Vecteur::operator* (double scalaire) const {
	Vecteur retour;
	for (size_t i(0) ; i < vecteur.size() ; i++) {
		retour.push_back(scalaire * vecteur[i]);
	}
	return retour;
}

const Vecteur Vecteur::operator^ (Vecteur const& autre) const { //produit vectoriel, uniquement en dimension 3
    if ((autre.vecteur.size() != vecteur.size()) || (vecteur.size()!=3)) throw Erreur("vecteur ^");
	Vecteur retour; 
	retour.push_back(vecteur[1]*autre.vecteur[2]-vecteur[2]*autre.vecteur[1]);
	retour.push_back(vecteur[2]*autre.vecteur[0]-vecteur[0]*autre.vecteur[2]);
	retour.push_back(vecteur[0]*autre.vecteur[1]-vecteur[1]*autre.vecteur[0]);
	return retour;
}

double Vecteur::operator[] (size_t i) const {
    if (vecteur.size() <= i) throw Erreur("Vecteur []");
	return vecteur[i];
}

double& Vecteur::operator[] (size_t i) {
    if (vecteur.size() <= i) throw Erreur("Vecteur &[]");
	return vecteur[i];
}

Vecteur& Vecteur::operator+= (Vecteur const& v) {
    if (v.vecteur.size() != vecteur.size()) throw Erreur("vecteur =addition");
	return *this = (*this + v);
}

Vecteur& Vecteur::operator-= (Vecteur const& v) {
    if (v.vecteur.size() != vecteur.size()) throw Erreur("vecteur =soustraction");
	return *this = (*this - v);
}

Vecteur& Vecteur::operator*= (double scalaire) {
	return (*this = (scalaire * *this));
}

Vecteur& Vecteur::operator^= (Vecteur const& v) {
    if (v.vecteur.size() != vecteur.size()) throw Erreur("vecteur =prodvect");
	return *this = (*this ^ v);
}

//
//inutile aux beneficiaires de la classe
//

void Vecteur::affiche (std::ostream&) const {
	std::cout << "(";
	for (size_t i(0); i < vecteur.size() ; i++) {
		std::cout << vecteur[i];
		if (i < vecteur.size()-1) std::cout << ", "; 
	}
	std::cout << ")";
}

//methodes externes
const Vecteur operator*(double b, Vecteur const& a) {
	return a * b;
}

std::ostream& operator<<(std::ostream& flux, Vecteur const& v) {
	v.affiche(flux);
	return flux;
}

double coplanaire (Vecteur a, Vecteur o, Vecteur L) {
    return a.prod_scal(o^L);
}
