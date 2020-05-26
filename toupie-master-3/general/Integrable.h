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
            Integrable (size_t);
            Integrable (std::vector<Vecteur>, size_t);
		
   		//destructeur
		
		//methodes 
            virtual Vecteur eq_evolution (std::vector<Vecteur> position , double temps = 0) = 0;
            Vecteur position (size_t) const;
            const Vecteur get_vect_P ();
            const Vecteur get_vect_dP ();

    //integrateurs
        	virtual void EulerCromer (double pas_de_temps, double temps = 0);
      	  	virtual void Newmark (double pas_de_temps, double temps = 0);
        	virtual void RungeKutta (double pas_de_temps, double temps = 0);
    
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;
			
	protected:
        std::vector<Vecteur> Position;

        virtual size_t degre () const = 0;
};

//methodes externes
std::ostream& operator<< (std::ostream&, Integrable const&);

#endif
