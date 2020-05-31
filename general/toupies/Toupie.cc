#include "Toupie.h"

//constructeurs
Toupie::Toupie (std::vector<Vecteur> p, double mv, double h, double r, bool move)
    : Integrable(p, degre_Position()), masseVolumique (mv), hauteur(h), rayon(r), moveXY(move)
{
    for (size_t i(0); i<p.size(); i++) {

        if (Position[i].size() == 3) {
            Position[i].push_back(0.);
            Position[i].push_back(0.);
        }
        if (Position[i].size() != 5) throw Erreur("vecteur Toupie");
    }
}

//integrateurs
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

//methodes
void Toupie::invertMoveXY() {
    moveXY = !moveXY;
}

void Toupie::modulo2pi(){
    Integrable::Position[0][0] = fmod(Integrable::Position[0][0], 2*pi);
    Integrable::Position[0][1] = fmod(Integrable::Position[0][1], 2*pi);
    Integrable::Position[0][2] = fmod(Integrable::Position[0][2], 2*pi);
}

//accesseurs
double Toupie::getHauteur() const {
    return hauteur;
}

double Toupie::getRayon() const {
    return rayon;
}

double Toupie::getMV() const {
    return masseVolumique;
}

//traces
void Toupie::recordTrace(double coeff){
    Vecteur XY(Position[1][3], Position[1][4], 0.);
    trace.add_vect( coeff * OG() + XY);
}

Vecteur Toupie::getVectNb(size_t nb) const {
    return trace.get_vect(nb);
}

size_t Toupie::nbVectTrace() const {
    return trace.taille();
}

void Toupie::clearTrace(){
    trace.clear();
}

//energie et invariants

double Toupie::energie_cin() const {
    return (0.5 * (masse () * vitesse_G_Rg().norme2()) + (vect_rot_Rg().prod_scal(moment_cin_G())));
}

double Toupie::energie_pot() const {
    return (masse() * (vecteur_g.prod_scal(OG ())));
}

double Toupie::energie_totale() const {
    return (energie_cin() + energie_pot());
}

double Toupie::invariant_vect_rot_Rg3 () const {
    return (vect_rot_Rg()[2]);
}

double Toupie::invariant_moment_cin_A3 () const {
    return (invariant_vect_rot_Rg3() * I3());
}

double Toupie::invariant_moment_cin_Az () const {
    return ((passage_RgRo() * moment_cin_A()).prod_scal(vect_k_Ro()));
}

double Toupie::invariant_coplanaires() const {
    return coplanaire((OG_Rg()), vect_rot_Rg(), moment_cin_G());
}

//
//Protected
//


Matrice33 Toupie::passage_RgRo () const {
    return Matrice33 (cos(PSI), sin(PSI), 0,
                      -cos(THETA) * sin(PSI), cos(PSI) * cos(THETA), sin(THETA),
                      sin(THETA) * sin(PSI), -sin(THETA) * cos(PSI), cos(THETA));
}

Matrice33 Toupie::passage_RoRg() const {
    return passage_RgRo().transp();
}

Matrice33 Toupie::inertie () const {
    return Matrice33 (I1(), I1(), I3());
}

//
Vecteur Toupie::OG_unitaire() const {
    return Vecteur (sin(THETA) * sin(PSI), -sin(THETA) * cos(PSI), cos(THETA));
}

Vecteur Toupie::OG_Rg () const {
    return (passage_RoRg() * OG());
}

Vecteur Toupie::vect_k_Ro() const {
    return Vecteur(cos(PSI), sin(PSI), 0);
}

Vecteur Toupie::moment_cin_G() const {
    return (inertie() * vect_rot_Rg());
}

Vecteur Toupie::moment_cin_A() const {
    return ((masse() * (OG_Rg() ^ vitesse_G_Rg())) + moment_cin_G());
}

Vecteur Toupie::vect_rot_Rg() const {
    return Vecteur (THETA_P, PSI_P * sin(THETA), (PSI_P * cos(THETA)) + PHI_P);
}

Vecteur Toupie::vect_rot_Ro() const {
    return (passage_RgRo() * vect_rot_Rg());
}

Vecteur Toupie::vect_rotDeRg_Rg() const {
    Vecteur v(0, 0, 1);
    return (vect_rot_Rg() - (PHI_P * v));}

Vecteur Toupie::vitesse_G_Rg() const {
    return (vect_rot_Rg() ^ OG_Rg());
}

Vecteur Toupie::vitesse_G_Ro() const {
    return (passage_RgRo() * vitesse_G_Rg());
}

double Toupie::masse () const {
    return masseVolumique * volume ();
}

size_t Toupie::degre_Position() const{
    return 2;
}
