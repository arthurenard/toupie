#ifndef H_MATRICE33
#define H_MATRICE33

#include <iostream> 
#include <array>
#include "Vecteur.h"

class Matrice33 {
	public:
		//constructeurs
		Matrice33 (double, double, double); //constructeur de matrice diagonale
		Matrice33 (double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0); //construit la matrice ligne par ligne
		
		//destructeur
		
		//methodes
		const Matrice33 transp() const;
		const Matrice33 inv () const;
		const double det() const;
		
		//operateurs internes
		bool operator== (Matrice33 const&) const;
		bool operator!= (Matrice33 const&) const;		
		const Matrice33 operator- () const; //retourne la matrice opposée
		const Matrice33 operator+ (Matrice33 const&) const;
		const Matrice33 operator- (Matrice33 const&) const;
		const Matrice33 operator* (Matrice33 const&) const;
		const Matrice33 operator* (double) const;
		Matrice33& operator+= (Matrice33 const&);
		Matrice33& operator-= (Matrice33 const&);	
		Matrice33& operator*= (Matrice33 const&);
		Matrice33& operator*= (double scalaire);
		
		Vecteur operator* (Vecteur const&) const;
		
		//inutile aux beneficiares de la classe
		void affiche (std::ostream&) const;
		
	private:
		std::array<std::array<double, 3>, 3> matrice;
		
		//methodes privees
};

//operateurs externes
const Matrice33 operator* (double, Matrice33 const&);
std::ostream& operator<< (std::ostream&, Matrice33 const&);

#endif
