#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include <vector>
#include <cmath> 

#include "Vecteur.h"
#include "constantes.h"

#define abs(nb) ((nb) < 0 ? -(nb) : (nb))

class Toupie {
	public: 
		//constructeurs
		Toupie (Vecteur vect_P = 0, Vecteur vect_dP = 0);
		Toupie (std::vector<double> vect_P, std::vector<double> vect_dP);
		//destructeur
		
		//methodes 
		Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0);
		
		void EulerCromer (double pas_de_temps, double temps = 0);
		void Newmark (double pas_de_temps, double temps = 0);
		void RungeKutta (double pas_de_temps, double temps = 0);
		
		
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;
			
	protected:
		Vecteur vect_P; // psi, theta, phi
		Vecteur vect_dP; // psi-point, theta-point, phi-point
};

//methodes externes
std::ostream& operator<< (std::ostream&, Toupie const&);

#endif
