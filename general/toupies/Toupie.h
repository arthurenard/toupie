#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include <vector> 

#include "bases/Vecteur.h"
#include "../Integrable.h"

class Toupie : public Integrable {
	public: 
		//constructeurs
		Toupie (Vecteur vect_P = 0, Vecteur vect_dP = 0);
		Toupie (std::vector<double> vect_P, std::vector<double> vect_dP);
};

#endif
