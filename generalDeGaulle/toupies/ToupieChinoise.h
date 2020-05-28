#ifndef H_TOUPIECHINOISE
#define H_TOUPIECHINOISE

#include <iostream> 
#include "Toupie.h"
#include "bases/constantes.h"

//on considere que la toupie chinoise est une sphere tronquee

class ToupieChinoise : public Toupie {
	public:
		// constructeurs
        ToupieChinoise (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon, bool move = false);

		// destructeurs
		
		//methodes publiques
		
		//operateurs internes
        Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;
        int getType() override;

		//methodes inutiles aux beneficiares
	
	
	protected: 
		//attributs

		
		//methodes privees
        	double volume () const override; // m3
        	double alpha () const;
        	double I1 () const override; // kg * m2
        	double I3 () const override; // kg * m2

        	Vecteur OG () const override; //on considere que G est le centre de la boule pour simplifier les calculs
    private:
            size_t degre () const override;
};


#endif
