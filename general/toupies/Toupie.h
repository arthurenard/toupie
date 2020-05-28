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
        Toupie (std::vector<Vecteur>, size_t degre, double masseVolumique = 1, double hauteur = 1.5, double rayon = 0.5, bool move = false); // psi, théta, phi, x, y ; les toupie sont au plus de degree 2

        virtual void EulerCromer(double pas_de_temps, double temps = 0) override;
        virtual void Newmark(double pas_de_temps, double temps = 0) override;
        virtual void RungeKutta(double pas_de_temps, double temps = 0) override;

        void modulo2pi();
        double getHauteur(){return hauteur;} // metre
        double getRayon(){return rayon;}
        double getMV(){return masseVolumique;}

        virtual int getType(){return 0;}

        void recordTrace();
        Vecteur getVectNb(size_t nb){return trace.get_vect(nb);}
        size_t nbVectTrace(){return trace.taille();}
        void clearTrace(){trace.clear();}

        double energie_totale () const;
        double invariant_vect_rot_Rg3 () const; //retourne la 3eme coordonnée de vect_rot_Rg qui devrait etre une constante
        double invariant_moment_cin_A3 () const; //retourne le I3 * invariant_vect_rot_Rg3 qui est une constante
        double invariant_moment_cin_Az () const; //retourne moment_cin_A * vect_k
        double invariant_coplanaires () const;
        double energie_cin () const;

        void invertMoveXY(){moveXY = !moveXY;}


    protected:
        //attributs
        double masseVolumique;
        double hauteur; // metre
        double rayon; // metre

        Memoire trace;

        //methodes
        Matrice33 passage_RgRo () const;
        Matrice33 passage_RoRg () const;
        Matrice33 inertie () const;

        Vecteur vect_k_Ro () const; //retourne le vecteur k dans la base Ro
        Vecteur moment_cin_G () const;
        Vecteur moment_cin_A () const;
        Vecteur vect_rot_Rg () const;
        Vecteur vect_rot_Ro () const;
        Vecteur vect_rotDeRg_Rg () const; //retourne le vecteur de rotation du repere Rg dans la base Rg
        Vecteur vitesse_G_Rg () const;
        Vecteur vitesse_G_Ro () const;
        Vecteur OG_unitaire () const;
        virtual Vecteur OG () const = 0;

        double masse () const;
        virtual double I1 () const = 0;
        virtual double I3 () const = 0;
        virtual double volume () const = 0;

        //Invariants
        double energie_pot () const;

        bool moveXY;


};

#endif
