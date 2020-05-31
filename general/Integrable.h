#ifndef H_INTEGRABLE
#define H_INTEGRABLE

#include <iostream>
#include <vector>
#include <cmath> 

#include "Erreur.h"
#include "bases/Vecteur.h"
#include "bases/constantes.h"

#define abs(nb) ((nb) < 0 ? -(nb) : (nb))

class Integrable {
	public: 
		//constructeurs
            Integrable (std::vector<Vecteur> Position, size_t degre_Position); //verifie si la dimension de Position est == à degre_Position, erreur sinon
		
   		//destructeur
            virtual ~Integrable()=default;

		
		//methodes 
            virtual Vecteur eq_evolution (std::vector<Vecteur> position , double temps = 0) const = 0;
            const Vecteur get_vect_P () const; //retourne Position[0]
            const Vecteur get_vect_dP () const; //retourne Position[1]

        //integrateurs
            virtual void EulerCromer (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Euler-Crommer de degré 1 et 2
            virtual void Newmark (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Newmark de degré 2
            virtual void RungeKutta (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Runge-Kutta de degré 1 et 2
    
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;
			
	protected:
        //attribut
        std::vector<Vecteur> Position;

        //methodes
        virtual size_t degre_Position () const = 0;
        virtual size_t degre_eqEvol () const = 0;
};

//methodes externes
std::ostream& operator<< (std::ostream&, Integrable const&);

#endif
