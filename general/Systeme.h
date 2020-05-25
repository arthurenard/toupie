#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 
#include <stdlib.h>
#include <time.h>

#include "bases/Vecteur.h"

#include "toupies/Toupie.h"
#include "toupies/ConeSimple.h"
#include "toupies/ToupieChinoise.h"

#include "dessinable.h"
#include "support_a_dessin.h"
#include "balle.h"




class Systeme : public Dessinable {
	public: 
    Systeme(SupportADessin* vue): Dessinable(vue), WTF(false){
        srand (time(NULL));
        //addCone();
        /*addToupie(new ConeSimple(Vecteur( 0.01, 0.01, 0.0, 0., 0.), Vecteur(0.0, 0.0, 180, 0., 0.), 1.0,1.5,0.5));
        addToupie(new ConeSimple(Vecteur( 0.01, 0.01, 0.0, 1., 1.), Vecteur(0.0, 0.0, 180, 0., 0.), 1.0,1.5,0.5));
        addToupie(new ToupieChinoise(Vecteur( 0.01, 0.01, 0.0, -2., 0.), Vecteur(0.0, 0.0, 180, 0., 0.), 1.0,1.5,0.5));

        types.push_back(0);
        integrateurs.push_back(0);
        types.push_back(0);
        integrateurs.push_back(2);
        types.push_back(1);
        integrateurs.push_back(2);
        //addToupie(0,0, 0.01, 0.01, 0.0,0.0,0.0,0.0, 0.0, 180)*/
    }

        virtual void dessine() override
        { support->dessine(*this); }

        void evolue(double dt);

        size_t nbToupies() const {return toupies.size(); }

        void addToupie(Toupie* newtoupie){toupies.push_back(newtoupie);}
        void addToupie(std::vector<double> data);

        void delToupie(size_t id);


        Toupie* getToupie(size_t nb) const;
        int getIntegrateur(size_t nb) const;

        const std::vector<Toupie*>* getToupies() const{
            return &toupies;
        }


        Balle* getBalle(size_t nb) const;
        void partyWTF(){WTF = true;}
        size_t nbBalles() const {return balles.size(); }
        double random(double min=0., double max=1.);
        void addBalle(Vecteur P, Vecteur dP);
        void suppBalle(size_t id);


        void invertTrace(){
            trace = !trace;
            for(size_t i(0); i < toupies.size() ; i++){
              toupies[i]->clearTrace();
                          }}
        bool getTrace() const{return trace;}
        void clearAll(){toupies.clear();
                       integrateurs.clear();
                       }
        std::vector<std::vector<double>> getAllData();

		
	protected:
        std::vector<Toupie*> toupies;
        std::vector<int> integrateurs;


        std::vector<Balle*> balles;
        bool WTF;

        bool trace;
        std::vector<double> getDataTop(size_t id);

};
double arrondis(double value);
#endif
