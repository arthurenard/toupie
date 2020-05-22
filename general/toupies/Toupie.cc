#include "Toupie.h"

//constructeurs
Toupie::Toupie (Vecteur v, Vecteur w, double mv, double h, double r)
    : masseVolumique (mv), hauteur(h), rayon(r)
{
	if (v.size() == 3) {
        v.push_back(0.);
        v.push_back(0.);
	}
    if (v.size() != 5) throw "Vecteur Toupie";

     Integrable::vect_P=v;
	
	if (w.size() == 3) {
        w.push_back(0.);
        w.push_back(0.);
	}
    if (w.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_dP = w;
}

Toupie::Toupie (std::vector<double> v, std::vector<double> w, double mv, double h, double r)
    : masseVolumique (mv), hauteur(h), rayon(r)
{
	if (v.size() == 3) {
        v.push_back(0.);
        v.push_back(0.);
	}
    if (v.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_P = v;

	if (w.size() == 3) {
        w.push_back(0.);
        w.push_back(0.);
	}
    if (w.size() != 5) throw "Vecteur Toupie";

    Integrable:: vect_dP = w;
}


void Toupie::EulerCromer(double pas_de_temps, double temps) {
    Integrable::EulerCromer(pas_de_temps, temps);
    modulo2pi();
}
void Toupie::RungeKutta(double pas_de_temps, double temps) {
    Integrable::RungeKutta(pas_de_temps, temps);
    modulo2pi();
}

void Toupie::Newmark(double pas_de_temps, double temps) {
    Integrable::Newmark(pas_de_temps, temps);
    modulo2pi();
}

void Toupie::modulo2pi(){
    Integrable::vect_P[0] = fmod(Integrable::vect_P[0], 2*pi);
    Integrable::vect_P[1] = fmod(Integrable::vect_P[1], 2*pi);
    Integrable::vect_P[2] = fmod(Integrable::vect_P[2], 2*pi);
}

Matrice33 Toupie::passage_RgRo () const {
    return Matrice33 (cos(PSI), sin(PSI), 0, -cos(THETA) * sin(PSI), cos(PSI) * cos(THETA), sin(THETA), sin(THETA) * sin(PSI), -sin(THETA) * cos(PSI), cos(THETA));
}

Matrice33 Toupie::passage_RoRg() const {
    return passage_RgRo().transp();
}

Matrice33 Toupie::inertie () const {
    return Matrice33 (I1(), I1(), I3());
}

Vecteur Toupie::moment_cin_G() const {
    return (inertie() * vect_rot_Rg());
}

Vecteur Toupie::vect_rot_Rg() const {
    return Vecteur (THETA_P, PSI_P * sin(THETA), (PSI_P * cos(THETA)) + PHI_P);
}

Vecteur Toupie::vect_rot_Ro() const {
    return (passage_RgRo() * vect_rot_Rg());
}

Vecteur Toupie::vitesse_G_Rg() const {
    return ((- OG()) ^ vect_rot_Rg());
}

Vecteur Toupie::vitesse_G_Ro() const {
    return (passage_RgRo() * vitesse_G_Rg());
}

Vecteur Toupie::OG_unitaire() const {
    return Vecteur (sin(THETA) * sin(PSI), -sin(THETA) * cos(PSI), cos(THETA));
}

double Toupie::masse () const {
    return masseVolumique * volume ();
}

double Toupie::energie_cin() const {
    return (0.5 * (masse () * vitesse_G_Rg().norme2()) + (vect_rot_Rg().prod_scal(moment_cin_G())));
}

double Toupie::energie_pot() const {
    return (masse() * (vecteur_g.prod_scal(OG () ) ) );
}

double Toupie::energie_totale() const {
    return (energie_cin() - energie_pot());
}

double Toupie::invariant_coplanaires() const {
    return coplanaire((OG_unitaire()), vect_rot_Rg(), moment_cin_G());
}
