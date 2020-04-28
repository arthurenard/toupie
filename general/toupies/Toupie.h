#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include <vector> 

#include "bases/Vecteur.h"
#include "../Integrable.h"

class Toupie : public Integrable {
	public: 
		//constructeurs
		Toupie (Vecteur vect_P = 0, Vecteur vect_dP = 0); // psi, théta, phi, x, y
		Toupie (std::vector<double> vect_P, std::vector<double> vect_dP); //psi-point, theta-point, phi-point, x-point, y-point
};

#endif
