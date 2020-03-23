#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include "Vecteur.h"

class Toupie {
	public: 
		//constructeurs
		
		//destructeur
		
    //methodes 
		Vecteur eq_evolution (unsigned long long int temps, Vecteur vect_P, Vecteur vect_dP);
		
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;
			
	private:
		Vecteur vect_P;
		Vecteur vect_dP;
};

//methodes externes
std::ostream& operator<< (std::ostream&, Toupie const&);

#endif
