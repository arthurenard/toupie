#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 
#include <stdlib.h>
#include <time.h>

#include "bases/Vecteur.h"

#include "Erreur.h"
#include "toupies/Toupie.h"
#include "toupies/ConeSimple.h"
#include "toupies/ToupieChinoise.h"
#include "toupies/ToupieG_Conique.h"
#include "toupies/ConiqueEnergetique.h"

#include "dessinable.h"
#include "support_a_dessin.h"
#include "balle.h"
#include "jcc.h"




class Systeme : public Dessinable {
    public:
        Systeme(SupportADessin* vue);
        ~Systeme();

        virtual void dessine() override;


        void evolue(double dt); //Appelle les integrateurs de chaques integrable du systeme; toupies et balles



        //Methodes de gestions des toupies :
        void addToupie(Toupie* newtoupie); //Ajoute un pointeur au vector de toupies*
        void addToupie(std::vector<double> data); //Ajoute une toupiee au systeme a partir de données brutes
        void delToupie(size_t nb); //permet de supprimer la toupie d'index nb
        size_t nbToupies() const; //retourne le nombre de toupies du systeme
        Toupie* getToupie(size_t nb) const; //retourne un pointeur vers la toupie d'index nb
        int getIntegrateur(size_t nb) const; //retourne le chiffre integrateur (0: Euler 1: NEwmark 2: RungeKutta) de la toupie d'index nb
        bool getTrace() const; //retourne la valeur de trace
        void invertTrace(); //inverse trace
        void invertConeFixe(); //inverse toupieFixe et moveXY de chaques toupies du systeme
        void clearAll(); // vide et delete les toupies et integrable


        //Methodes de gestions des balles :
        Balle* getBalle(size_t nb) const; //retourne un pointeur vers la balle d'index nb
        void addBalle(std::vector<Vecteur>); //Ajoute une balle a partir d'un vector<Vecteur>{(X,Y,Z),(Xpoint,Ypoint,Zpoint)}
        void suppBalle(size_t nb);//Supprime la balle d'index nb
        size_t nbBalles() const;//Retourne le nombre de balles du systeme
        double random(double min=0., double max=1.);//Sort un double aleatoire entre min et max (quand ils sont petits)

        void partyWTF();//SURPRISE
        bool getWTF() const;//SURPRISE
        double getNyan() const;//SURPRISE

        std::vector<std::vector<double>> getAllData(); //retourne toutes les données liées aux toupies


	protected:
        std::vector<Toupie*> toupies;
        std::vector<int> integrateurs;
        std::vector<Balle*> balles;
        JCC* nyan;

        bool toupieFixe;
        bool trace;
        bool WTF;

        std::vector<double> getDataTop(size_t nb);//Retourne toutes les données de la toupie d'index nb


};
double arrondis(double value);
#endif
