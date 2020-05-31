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
        ~ConeSimple()=default;

		//methodes publiques
        int getType() const override; //retourne un numero qui symbolise le type de la toupie
        Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) const override;
	
    private:
        //attributs

        //methodes privées
        virtual size_t degre_eqEvol () const override; //retourne le degre des equations d'evolution
};

#endif
