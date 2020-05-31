#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include <vector> 

#include "bases/Vecteur.h"
#include "bases/Matrice33.h"
#include "../Integrable.h"
#include "Memoire.h"

#define PSI (Position[0][0])
#define THETA (Position[0][1])
#define PHI (Position[0][2])
#define PSI_P (Position[1][0])
#define THETA_P (Position[1][1])
#define PHI_P (Position[1][2])
#define CONIQUE (0)
#define CHINOISE (1)
#define CONIQUEG (2)
#define CONIQUEE (3)

/*
 * Base Ro = (O, x, y, z) repere galileen de reference
 * Base Rg (G, u, b, a) un repere d'inertie du solide, a etant l'axe principal de la toupie)
 *
 * O est donc l'origine de Ro
 * G (centre de gravité) est donc l'origine de Rg
 * A est le point de contact entre la toupie et le plan (x, y) de Ro
 *      -> dans les equations il a souvent été considéré que A = O
 */

class Toupie : public Integrable {
	public: 
        //constructeurs
        Toupie (std::vector<Vecteur>, double masseVolumique = 1, double hauteur = 1.5, double rayon = 0.5, bool move = false); // psi, théta, phi, x, y ; les toupie sont au plus de degree 2

        //destructeurs
        virtual  ~Toupie()=default;

        //methodes
            void invertMoveXY(); //inverse moveXY
            void modulo2pi(); //renvoie le vecteur Position[0] (le vect-P) dont les 3premières coordonnées (des angles en radians) %= 2π (pour des réels)

            //Integrateurs numeriques (appelle la methode modulo 2π après l'appel des intégrateurs numériques)
            virtual void EulerCromer(double pas_de_temps, double temps = 0) override; //l'intégrateur numérique de Euler-Crommer de degré 1 et 2
            virtual void Newmark(double pas_de_temps, double temps = 0) override; //l'intégrateur numérique de Newmark de degré 2
            virtual void RungeKutta(double pas_de_temps, double temps = 0) override; //l'intégrateur numérique de Runge-Kutta de degré 1 et 2

            //accesseurs
            double getHauteur() const; // retourne la hauteur en metre
            double getRayon() const; //retourne le rayon en metre
            double getMV() const; //retourne la masse volumique en kg m-3
            virtual int getType() const = 0; //retourne un entier qui représente le type de la toupie

            //traces
            void recordTrace(double facteur_multiplicateur= 2.5); //enregistre la trace de OG
            Vecteur getVectNb(size_t nb) const; //retourne le ieme - 1 vecteur de la Memoire trace
            size_t nbVectTrace() const; //retourne la taille de la Memoire trace
            void clearTrace(); //supprime toutes les valeurs de la Memoire trace

            //energie et invariants
            double energie_pot () const; //renvoie l'energie potentielle de la toupie
            double energie_cin () const; //renvoie l'energie cinetique de la toupie
            double energie_totale () const; //renvoie l'energie totale de la toupie (=potentielle + cinetique)
            double invariant_vect_rot_Rg3 () const; //retourne la 3eme coordonnée de vect_rot_Rg qui devrait etre une constante
            double invariant_moment_cin_A3 () const; //retourne le I3 * invariant_vect_rot_Rg3 qui est une constante
            double invariant_moment_cin_Az () const; //retourne moment_cin_A * vect_k
            double invariant_coplanaires () const; //verifie que OG, vect_rot et moment cin

    protected:
        //attributs
        double masseVolumique; //kg m-3
        double hauteur; // metre
        double rayon; // metre

        Memoire trace; //Crée une Memoire pour pouvoir stocker les positions de la trace de OG

        //methodes
        Matrice33 passage_RgRo () const; //matrice de passage entre Rg et Ro
        Matrice33 passage_RoRg () const; //matrice de passage entre Ro et Rg
        Matrice33 inertie () const; //matrice d'inertie au point G dans Rg

        Vecteur OG_unitaire () const; //retourne le vecteur OG unitaire dans la base Ro
        virtual Vecteur OG () const = 0; //retourne le vecteur OG dans la base Ro
        Vecteur OG_Rg () const; //retourne le vecteur OG dans la base Rg
        Vecteur vect_k_Ro () const; //retourne le vecteur k dans la base Ro
        Vecteur moment_cin_G () const; //retourne le moment cin en G dans la base Rg
        Vecteur moment_cin_A () const; //retourne le moment cin en A dans la base Rg
        Vecteur vect_rot_Rg () const; //retourne le vecteur de rotation (omega) dans la base Rg
        Vecteur vect_rot_Ro () const; //retourne le vecteur de rotation (omega) dans la base Ro
        Vecteur vect_rotDeRg_Rg () const; //retourne le vecteur de rotation du repere Rg dans la base Rg
        Vecteur vitesse_G_Rg () const; //retourne la vitesse de G dans la base Rg
        Vecteur vitesse_G_Ro () const; //retourne la vitesse de G dans la base Ro

        double masse () const;
        virtual double I1 () const = 0; //composante de la matrice d'inertie diagonale de G dans Rg diagonale, I2 = I1
        virtual double I3 () const = 0; //composante de la matrice d'inertie diagonale de G dans Rg diagonale
        virtual double volume () const = 0; //retourne le volume en m3

        bool moveXY; //active le déplacement des toupies ou non
        //attributs
        size_t degre_Position() const override; //retourne le nombre de Vecteur qu'aura Position
};

#endif
