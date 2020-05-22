#ifndef H_TOUPIE
#define H_TOUPIE

#include <iostream>
#include <vector> 

#include "bases/Vecteur.h"
#include "bases/Matrice33.h"
#include "../Integrable.h"

#define PSI (vect_P[0])
#define THETA (vect_P[1])
#define PHI (vect_P[2])
#define PSI_P (vect_dP[0])
#define THETA_P (vect_dP[1])
#define PHI_P (vect_dP[2])

/*
 * Base Ro = (O, x, y, z) repere galileen de reference
 * Base Rg (G, u, b, a) un repere d'inertie du solide, a etant l'axe principal de la toupie)
 *
 */
class Toupie : public Integrable {
	public: 
		//constructeurs
        Toupie (Vecteur vect_P = 0, Vecteur vect_dP = 0, double masseVolumique = 1); // psi, théta, phi, x, y
        Toupie (std::vector<double> vect_P, std::vector<double> vect_dP, double masseVolumique = 1); //psi-point, theta-point, phi-point, x-point, y-point

        virtual void EulerCromer(double pas_de_temps, double temps = 0) override;
        virtual void Newmark(double pas_de_temps, double temps = 0) override;
        virtual void RungeKutta(double pas_de_temps, double temps = 0) override;

        void modulo2pi();

    protected:
        //attributs
        double masseVolumique;

        //methodes
        Matrice33 passage_RgRo () const;
        Matrice33 passage_RoRg () const;
        Matrice33 inertie () const;

        Vecteur moment_cin_G () const;
        Vecteur vect_rot_Rg () const;
        Vecteur vect_rot_Ro () const;
        Vecteur vitesse_G_Rg () const;
        Vecteur vitesse_G_Ro () const;
        Vecteur OG_unitaire () const;
        virtual Vecteur OG () const = 0;

        double masse () const;
        virtual double I1 () const = 0;
        virtual double I3 () const = 0;
        virtual double volume () const = 0;

        //Invariants
        double energie_cin () const;
        double energie_pot () const;
        double energie_totale () const;
        double invariant_coplanaires () const; //calcule coplanaire( (0, 0, 1), vect_rot_Rg, moment_cin_G), renvoie "0" si ils sont coplanaires
};

#endif
