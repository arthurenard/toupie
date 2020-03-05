#include <iostream> 
#include <array>
#include "Vecteur.h"

class Matrice33 {
	public:
		//constructeurs
		Matrice33 (double, double, double); //constructeur de matrice diagonale
		Matrice33 (double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0); //construit la matrice ligne par ligne
		
		//methodes
		Matrice33 transp() const;
		Matrice33 inv () const;
		double det() const;
		
		//operateurs
		bool operator== (Matrice33 const&) const;
		bool operator!= (Matrice33 const&) const;		
		const Matrice33 operator- () const; //retourne la matrice opposée
		Matrice33 operator+ (Matrice33 const&) const;
		Matrice33 operator- (Matrice33 const&) const;
		Matrice33 operator* (double) const;
		Matrice33& operator+= (Matrice33 const&);
		Matrice33& operator-= (Matrice33 const&);		
		Matrice33& operator*= (double scalaire);
		//Vecteur operator* (Vecteur const&) const;
		
		//methode pour le devellopur
		void affiche (std::ostream&) const;
		
	private:
		std::array<std::array<double, 3>, 3> matrice;
		
		//methodes privees
};

//operateurs externes
const Matrice33 operator* (double, Matrice33 const&);
std::ostream& operator<< (std::ostream&, Matrice33 const&);
