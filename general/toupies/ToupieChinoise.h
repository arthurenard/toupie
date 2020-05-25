#ifndef H_TOUPIECHINOISE
#define H_TOUPIECHINOISE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

//on considere que la toupie chinoise est une sphere tronquee

class ToupieChinoise : public Toupie {
	public:
		// constructeurs
        ToupieChinoise (Vecteur vect_P, Vecteur vect_dP, double masseVolumique, double hauteur, double rayon);
        ToupieChinoise (std::vector<double> vect_P, std::vector<double> vect_dP, double masseVolumique, double hauteur, double rayon);
		
		// destructeurs
		
		//methodes publiques
		
		//operateurs internes
        	virtual Vecteur eq_evolution (Vecteur P = 0, Vecteur dP = 0, double temps = 0) override;
        virtual int getType() override;
		
		//methodes inutiles aux beneficiares
	
	
	protected: 
		//attributs

		
		//methodes privees
        	double volume () const override; // m3
        	double alpha () const;
        	double I1 () const override; // kg * m2
        	double I3 () const override; // kg * m2

        	Vecteur OG () const override; //on considere que G est le centre de la boule pour simplifier les calculs
};


#endif
