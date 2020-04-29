#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 

#include "bases/Vecteur.h"

#include "toupies/Toupie.h"
#include "toupies/ConeSimple.h"
#include "toupies/ToupieChinoise.h"

#include "dessinable.h"
#include "support_a_dessin.h"



class Systeme : public Dessinable {
	public: 
    Systeme(SupportADessin* vue): Dessinable(vue)
    {
        addCone();
        //addToupie(new ConeSimple(Vecteur( 0.01, 0.01, 0.0), Vecteur(0.0, 0.0, 180), 1.0,1.5,0.5));
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
            Vecteur P( 0.01, 0.01, 0.0, 1.0, 0.0);
            Vecteur dP( 0.0, 0.0, 180,0.0,0.0);
           cone= new ConeSimple(P, dP, 1.0,1.5,0.5) ;

           Vecteur P2( 0.01, 0.21, 0.0, -1.0, 0.0);
           Vecteur dP2( 0.0, 0.0, 0.0,0.0,0.0);
          cone2= new ConeSimple(P2, dP2, 1.0,1.5,0.5) ;
          Vecteur P3( 0.2, 0.2, 0.0, 0.0, 0.0);
          Vecteur dP3( 0.0, 0.0, 60,0.0,0.0);
         chinoise= new ToupieChinoise(P3, dP3, 0.5,1.0,0.3) ;
        }
        ConeSimple* getCone() const{
            return cone;
        }
        ConeSimple* getCone2() const{
            return cone2;
        }
        ToupieChinoise* getChinois() const{
            return chinoise;
        }
        const std::vector<Toupie*>* getToupies() const{
            return &toupies;
        }
		
	protected:
        std::vector<Toupie*> toupies;
        ConeSimple* cone;
        ConeSimple* cone2;
        ToupieChinoise* chinoise;

};

#endif
