#include "Integrable.h"

//constructeurs
Integrable::Integrable () {
    for (size_t i(0); i<degre() ; i++) {
        Position.push_back({});
    }
}

Integrable::Integrable (std::vector<Vecteur> p) {
    if (p.size() > degre()) throw "Integrable Degre";
    Position = p;
}

/*
Integrable::Integrable (Vecteur v):
    Integrable(1)
{
    Position[0] = v;
}

Integrable::Integrable (Vecteur v, Vecteur w) :
    Integrable (2)
{
    Position[0] = v;
    Position[1] = w;
}

Integrable::Integrable (std::vector<double> v) :
    Integrable(1)
{
    Position[0] = v;
}

Integrable::Integrable (std::vector<double> v, std::vector<double> w) :
  Integrable (2)
{
    Position[0] = v;
    Position[1] = w;
}
*/

//methodes publiques
Vecteur Integrable::position (size_t i) const {
    if (degre() >= i) throw "Erreur degree get Position";
    return Position[i];
}

const Vecteur Integrable::get_vect_P (){
    return position(0);
}
const Vecteur Integrable::get_vect_dP (){
    return position(1);
}

void Integrable::EulerCromer (double dt, double temps) {
    switch(degre()) {
    case 1: {
        Position[0] += dt * eq_evolution(Position, temps);
    }break;

    case 2: {
        Position[1] += dt * eq_evolution(Position, temps);
        Position[0] += dt * Position[1];
    }break;

    default: throw "Erreur degree EulerCrommer";
    }
}


void Integrable::Newmark (double dt, double temps) {
    switch(degre()) {
    case 2: {
        double T0 = temps;
        double T1 = dt + T0;
        Vecteur P0 = Position[0];
        Vecteur P1 = P0;
        Vecteur dP0 = Position[1];
        Vecteur dP1 = dP0;
        std::vector<Vecteur> p0 = Position;
            p0[0] = P0;
            p0[1] = dP0;
        Vecteur s = eq_evolution(p0, T0);
        Vecteur q, r;

        do {
            q = P1;
            std::vector<Vecteur> pr = Position;
                pr[0] = P1;
                pr[1] = dP1;
            r = eq_evolution(pr, T1);
            dP1 = dP0 + (0.5 * dt * (r + s));
            P1 = P0 + (dt * dP0) + ((1./3.) * dt * dt * ((0.5 * r) + s));
        } while ((P1 - q).norme() >= epsilon);

        Position[0] = P1;
        Position[1] = dP1;
    }break;

    default: throw "Erreur de degree Newmark";
    }
}

void Integrable::RungeKutta (double dt, double temps) {
    switch (degre()) {
    case 1: {
        Vecteur k1 (eq_evolution(Position, temps));
        std::vector<Vecteur> pk1 = Position;
        pk1[0] += 0.5 * dt * k1;
        Vecteur k2 (eq_evolution(pk1, temps + (0.5 * dt)));
        std::vector<Vecteur> pk2 = Position;
        pk2[0] += 0.5 * dt * k2;
        Vecteur k3 (eq_evolution(pk2, temps + (0.5 * dt)));
        std::vector<Vecteur> pk3 = Position;
        pk3[0] += dt * k3;
        Vecteur k4 (eq_evolution(pk3, temps + (0.5 * dt)));

        Position[0] += (1./6.) * dt * (k1 + 2*k2 + 2*k3 + k4);

    } break;

    case 2: {
        Vecteur k1 (Position[1]);
        Vecteur k1b (eq_evolution(Position, temps));
        Vecteur k2 (Position[1] + ((dt/2) * k1b));
        std::vector<Vecteur> pk2b = Position;
        pk2b[0] += 0.5 * dt * k1;
        pk2b[1] += 0.5 * dt *k1b;
        Vecteur k2b (eq_evolution (pk2b, temps + dt/2));
        Vecteur k3 (Position[1] + ((dt/2) * k2b));
        std::vector<Vecteur> pk3b = Position;
        pk3b[0] += 0.5 * dt * k2;
        pk3b[1] += 0.5 * dt *k2b;
        Vecteur k3b (eq_evolution (pk3b, temps + dt/2));
        Vecteur k4 (Position[1] + (dt * k3b));
        std::vector<Vecteur> pk4b = Position;
        pk4b[0] += dt * k3;
        pk4b[1] += dt *k3b;
        Vecteur k4b (eq_evolution (pk4b, temps));
	
        Position[0] += ((dt/6) * (k1 + (2*k2) + (2*k3) + k4));
        Position[1] += ((dt/6) * (k1b + (2*k2b) + (2*k3b) + k4b));
        } break;

    default: throw "Erreur de degree RungeKutta";
    }
}

//methodes protegees

//methodes inutiles aux beneficiaires
void Integrable::affiche (std::ostream &flux) const {
    std::cout << "P: " << Position[0] << "\n" << "dP: " << Position[1] << "\n";
}


//operateurs externes
std::ostream& operator<<(std::ostream& flux, Integrable const& t) {
	t.affiche(flux);
	return flux;
}
