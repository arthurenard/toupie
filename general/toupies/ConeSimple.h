#ifndef H_CONESIMPLE
#define H_CONESIMPLE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

class ConeSimple : public Toupie {
	public:
		// constructeurs
        ConeSimple();
		ConeSimple (Vecteur vect_P, Vecteur vect_dP, double masseVolumique, double hauteur, double rayon);
		ConeSimple (std::vector<double> vect_P, std::vector<double> vect_dP, double masseVolumique, double hauteur, double rayon);
		
		// destructeurs
		
		//methodes publiques
        virtual Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0) override;
        //accesseurs
        double getHauteur(){return hauteur;} // metre
        double getRayon(){return rayon;}
		//operateurs internes


		//methodes inutiles aux beneficiares
	

	private: 
		//attributs
		double masseVolumique; // kg*m⁻3
		double hauteur; // metre
		double rayon; // metre
		
		//methodes privees
		const double volume () const; // m3
		const double masse () const; // kg
		const double I1 () const; // kg * m2 
		const double I3 () const; // kg * m2
		const double IA1 () const; // kg * m2
		const double MA () const;
};

#endif
