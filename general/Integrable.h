#ifndef H_INTEGRABLE
#define H_INTEGRABLE

#include <iostream>
#include <vector>
#include <cmath> 

#include "bases/Vecteur.h"
#include "bases/constantes.h"

#define abs(nb) ((nb) < 0 ? -(nb) : (nb))

class Integrable {
	public: 
		//constructeurs
		Integrable (Vecteur vect_P = 0, Vecteur vect_dP = 0);
		Integrable (std::vector<double> vect_P, std::vector<double> vect_dP);
		
   		//destructeur
		
		//methodes 
   		virtual Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0) = 0;
    		const Vecteur get_vect_P const ();
    
    		void EulerCromer (double pas_de_temps, double temps = 0);
		void Newmark (double pas_de_temps, double temps = 0);
		void RungeKutta (double pas_de_temps, double temps = 0);
    
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;
			
	protected:
		Vecteur vect_P; 
		Vecteur vect_dP;
};

//methodes externes
std::ostream& operator<< (std::ostream&, Integrable const&);

#endif
