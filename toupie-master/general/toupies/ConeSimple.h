#ifndef H_CONESIMPLE
#define H_CONESIMPLE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

class ConeSimple : public Toupie {
	public:
		// constructeurs
            ConeSimple ();
		ConeSimple (Vecteur vect_P, Vecteur vect_dP, double masseVolumique, double hauteur, double rayon);
		ConeSimple (std::vector<double> vect_P, std::vector<double> vect_dP, double masseVolumique, double hauteur, double rayon);
		
		// destructeurs
		
		//methodes publiques
        	virtual Vecteur eq_evolution (Vecteur P = 0, Vecteur dP = 0, double temps = 0) override;
        	//accesseurs

		//operateurs internes


		//methodes inutiles aux beneficiares
	

    protected:
		//attributs

		
		//methodes privees
       		double volume () const override; // m3
        	double I1 () const override; // kg * m2
        	double I3 () const override; // kg * m2
       		double IA1 () const; // kg * m2
        	double MA () const;
            double d () const; //retourne ||OG|| (=3/4 de la hauteur)

        Vecteur OG() const override;
};

#endif
