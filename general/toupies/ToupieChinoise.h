#ifndef H_TOUPIECHINOISE
#define H_TOUPIECHINOISE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

//on considere que la toupie chinoise est une sphere tronquee

class ToupieChinoise : public Toupie {
	public:
		// constructeurs
		ToupieChinoise (Vecteur vect_P, Vecteur vect_dP, double masseVolumique, double rayon, double hauteur);
		ToupieChinoise (std::vector<double> vect_P, std::vector<double> vect_dP, double masseVolumique, double rayon, double hauteur);
		
		// destructeurs
		
		//methodes publiques
		
		//operateurs internes
        virtual Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0) override;
		
		//methodes inutiles aux beneficiares
	
	
	protected: 
		//attributs
		double masseVolumique; // kg*m⁻3
		double rayon; // metre
		double hauteur; // metre
		
		//methodes privees
		const double masse () const; // kg
		const double volume () const; // m3
		const double alpha () const;
		const double I1 () const; // kg * m2
		const double I3 () const; // kg * m2
};


#endif
