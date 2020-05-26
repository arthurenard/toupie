#ifndef H_CONESIMPLE
#define H_CONESIMPLE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

class ConeSimple : public Toupie {
	public:
		// constructeurs
        ConeSimple (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon);
		
		// destructeurs
		
		//methodes publiques
        virtual Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;

        virtual int getType() override;
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

    private:
        size_t degre () const override;
};

#endif
