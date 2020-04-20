#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 

#include "toupies/Toupie.h"
#include "toupies/ConeSimple.h"
#include "dessinable.h"
#include "support_a_dessin.h"



class Systeme : public Dessinable {
	public: 
    Systeme(SupportADessin* vue): Dessinable(vue){
        addToupie(new ConeSimple);
    }

		virtual void dessine() override
        { support->dessine(*this); }

        void evolue(double dt);

        size_t nbToupies() const {return toupies.size(); }

        void addToupie(Toupie* newtoupie){toupies.push_back(newtoupie);}

        Toupie* getToupie(size_t nb) const {
            return toupies[nb];
        }
		
	protected:
        std::vector<Toupie*> toupies;

};

#endif
