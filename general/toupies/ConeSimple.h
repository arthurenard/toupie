#ifndef H_CONESIMPLE
#define H_CONESIMPLE

#include <iostream> 
#include "Cone.h"
#include "bases/constantes.h"

class ConeSimple : public Cone {
	public:
		// constructeurs
        ConeSimple (std::vector<Vecteur>, double masseVolumique, double hauteur, double rayon, bool move = false);
		
		// destructeurs
		
		//methodes publiques
        Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;



        int getType() override;
        	//accesseurs

		//operateurs internes


		//methodes inutiles aux beneficiares
	
    private:
        virtual size_t degre () const override;
};

#endif
