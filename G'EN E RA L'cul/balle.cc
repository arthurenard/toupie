#include "balle.h"

//constructeur
Balle::Balle(std::vector<Vecteur> p, double r, double v, double b) :
    Integrable(p, degre_Position()),
    rayon(0.1),
    coefRest(1.02)
{
    rvb.push_back(r);
    rvb.push_back(v);
    rvb.push_back(b);
}

//methode
Vecteur Balle::eq_evolution (std::vector<Vecteur>, double) const {
    return vecteur_g;
}

void Balle::EulerCromer(double pas_de_temps, double temps){
    Integrable::EulerCromer(pas_de_temps, temps);
    if (Position[0][2] - rayon< 0 ){
        Position[1][2]*= -coefRest;
        Position[0][2]=rayon;
    }
}

double Balle::getRayon() {
    return rayon;
}

std::vector<double> Balle::getRVB() {
    return rvb;
}

bool Balle::ouTof(){
    if (abs(Position[0][0]) > 10 || abs(Position[0][1]) > 10 ) //les limites du terrain
        return true;
    return false;
}

size_t Balle::degre_Position() const {
    return 2;
}

size_t Balle::degre_eqEvol() const {
    return 2;
}
