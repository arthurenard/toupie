#include "Matrice33.h"
//
//constructeurs
//
Matrice33::Matrice33 (double a, double b, double c) :
    Matrice33(a, 0., 0., 0., b, 0., 0., 0., c)
{}

Matrice33::Matrice33 (double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    matrice[0][0] = a;
    matrice[0][1] = b;
    matrice[0][2] = c;
    matrice[1][0] = d;
    matrice[1][1] = e;
    matrice[1][2] = f;
    matrice[2][0] = g;
    matrice[2][1] = h;
    matrice[2][2] = i;
}

//
//destructeur
//

//
//methodes
//
const Matrice33 Matrice33::transp () const {
    return Matrice33 (matrice[0][0], matrice[1][0], matrice[2][0], matrice[0][1], matrice[1][1],
            matrice[2][1], matrice[0][2], matrice[1][2], matrice[2][2]);
}

const Matrice33 Matrice33::inv () const {
	
	
    if (abs(this->det()) < epsilon) throw Erreur("Matrice33 inverse det nul");
	 
	Matrice33 r;
	r.matrice[0][0] = (matrice[1][1]*matrice[2][2] - matrice[1][2]*matrice[2][1]);
	r.matrice[0][1] = (matrice[0][2]*matrice[2][1] - matrice[0][1]*matrice[2][2]);
	r.matrice[0][2] = (matrice[0][1]*matrice[1][2] - matrice[0][2]*matrice[1][1]);
	r.matrice[1][0] = (matrice[1][2]*matrice[2][0] - matrice[1][0]*matrice[2][2]);
	r.matrice[1][1] = (matrice[0][0]*matrice[2][2] - matrice[0][2]*matrice[2][0]);
	r.matrice[1][2] = (matrice[0][2]*matrice[1][0] - matrice[0][0]*matrice[1][2]);
	r.matrice[2][0] = (matrice[1][0]*matrice[2][1] - matrice[2][0]*matrice[1][1]);
	r.matrice[2][1] = (matrice[0][1]*matrice[2][0] - matrice[0][0]*matrice[2][1]);
	r.matrice[2][2] = (matrice[0][0]*matrice[1][1] - matrice[0][1]*matrice[1][0]);
	
	return r*(1/this->det());
}

double Matrice33::det () const { //calcul le déterminant via la règle de Sarrus
        return matrice[0][0] * (matrice[1][1]*matrice[2][2] - matrice[1][2]*matrice[2][1]) -
                matrice[1][0] * (matrice[0][1]*matrice[2][2] - matrice[0][2]*matrice[2][1]) +
                matrice[2][0] * (matrice[0][1]*matrice[1][2] - matrice[1][1]*matrice[0][2]);
}

//operateurs internes

bool Matrice33::operator== (Matrice33 const& m) const {
		for(size_t a(0); a<3; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			if (matrice[a][b] != m.matrice[a][b]) return false;
		}
	}
	return true;
}

bool Matrice33::operator!= (Matrice33 const& m) const {
	return !(*this == m);
}

const Matrice33 Matrice33::operator- () const {
	Matrice33 m;
	for(size_t a(0); a<3; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			m.matrice[a][b] = -matrice[a][b];
		}
	}
	return m;
}


const Matrice33 Matrice33::operator+ (Matrice33 const& autre) const {
	Matrice33 m;
	for(size_t a(0); a<3; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			m.matrice[a][b] = matrice[a][b] + autre.matrice[a][b];
		}
	}
	return m;
}


const Matrice33 Matrice33::operator- (Matrice33 const& autre) const {
	Matrice33 m;
	for(size_t a(0); a<3; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			m.matrice[a][b] = matrice[a][b] - autre.matrice[a][b];
		}
	}
	return m;
}

const Matrice33 Matrice33::operator* (Matrice33 const& autre) const {
	Matrice33 retour(0.,0.,0.);
	for (size_t a(0) ; a<3 ; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			for (size_t c(0) ; c < 3 ; c++) {
				retour.matrice[a][b] += matrice[a][c] * autre.matrice[c][b];
			}
		}
	}
	return retour;
 }

const Matrice33 Matrice33::operator* (double d) const {
	Matrice33 m;
	for(size_t a(0); a<3; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			m.matrice[a][b] = matrice[a][b]*d;
		}
	}
	return m;
}

Matrice33& Matrice33::operator+= (Matrice33 const& m) {
	return *this = *this + m;
}

Matrice33& Matrice33::operator-= (Matrice33 const& m) {
	return *this = *this - m;
}

Matrice33& Matrice33::operator*= (Matrice33 const& m) {
	return *this = *this * m;
}

Matrice33& Matrice33::operator*= (double d) {
	return *this = *this * d;
} 

Vecteur Matrice33::operator* (Vecteur const& v) const {
    if (v.size() != 3) throw "matrice * vecteur"; //lance une erreur si la dimension du vecteur est differente de 3
	Vecteur retour(0, 0, 0);
	for (size_t a(0) ; a<3 ; a++) {
		for (size_t b(0) ; b<3 ; b++) {
			retour[a] += matrice[a][b] * v[b];
		}
	}
	return retour;
}

//
//methodes inutiles aux beneficiaires de la classe
//

void Matrice33::affiche (std::ostream&) const {
	std::cout << "{";
	for (size_t a(0) ; a<3 ; a++) {
		std::cout << "{";
		for (size_t b(0) ; b<3 ; b++) {
			std::cout << matrice[a][b] << ", ";
		}
		std::cout << "}";
		if (a!=2) std::cout << ",\n";
	}
	std::cout << "}";
}

//
//operateurs externes
//

const Matrice33 operator* (double d, Matrice33 const& m) {
	return m*d;
}

std::ostream& operator<< (std::ostream& flux, Matrice33 const& m) {
	m.affiche(flux);
	return flux;
}
