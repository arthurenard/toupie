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
        	Integrable (Vecteur v = 0, Vecteur w = 0);
        	Integrable (std::vector<double> v, std::vector<double> w);
		
   		//destructeur
		
		//methodes 
        	virtual Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0) = 0;
        	const Vecteur get_vect_P ();
            const Vecteur get_vect_dP ();

    
        	virtual void EulerCromer (double pas_de_temps, double temps = 0);
      	  	virtual void Newmark (double pas_de_temps, double temps = 0);
        	virtual void RungeKutta (double pas_de_temps, double temps = 0);
    
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
