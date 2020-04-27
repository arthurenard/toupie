#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 

#include "bases/Vecteur.h"

#include "toupies/Toupie.h"
#include "toupies/ConeSimple.h"

#include "dessinable.h"
#include "support_a_dessin.h"



class Systeme : public Dessinable {
	public: 
    Systeme(SupportADessin* vue): Dessinable(vue)
    {
        addCone();
    }

        virtual void dessine() override
        { support->dessine(*this); }

        void evolue(double dt);

        size_t nbToupies() const {return toupies.size(); }

        void addToupie(Toupie* newtoupie){toupies.push_back(newtoupie);}

        Toupie* getToupie(size_t nb) const {
            return toupies[nb];
        }
        void addCone(){
            Vecteur P( 0., 0.1, 0.0);
            Vecteur dP( 0.0, 0.0, 180);
           cone= new ConeSimple(P, dP, 1.0,1.5,0.5) ;
        }
        ConeSimple* getCone() const{
            return cone;
        }
		
	protected:
        std::vector<Toupie*> toupies;
        ConeSimple* cone;

};

#endif
