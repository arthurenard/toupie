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
         ~ToupieChinoise()=default;
				
		//operateurs internes
        Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) const override;
        int getType() const override; //retourne un numero qui symbolise le type de la toupie
	
    private:
		//attributs

		
		//methodes privees
        	double volume () const override; // m3
            double alpha () const; //retourne alpha
        	double I1 () const override; // kg * m2
        	double I3 () const override; // kg * m2

            Vecteur OG () const override; /*pas exactement OG dans ce cas ci, retourne le vecteur passant par l'axe de symetrie,
allant de l'extremite opposée à la partie tronquée jusqu'au centre de gravité G*/
            size_t degre_eqEvol () const override; //retourne le degré des équations d'évolution (ici 2)
};


#endif
