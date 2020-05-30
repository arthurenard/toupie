#include "Integrable.h"

//constructeurs
Integrable::Integrable (std::vector<Vecteur> p, size_t d) {
    if (p.size() != d) throw Erreur("Integrable Degre");
    Position = p;
}

//methodes publiques
const Vecteur Integrable::get_vect_P () const {
    return Position[0];
}
const Vecteur Integrable::get_vect_dP () const {
    if (Position.size() < 2) throw Erreur("Integrable get vect_dP");
    return Position[1];
}


//intgerateurs
void Integrable::EulerCromer (double dt, double temps) {
    switch(degre_eqEvol()) {
    case 1: {
        Position[0] += dt * eq_evolution(Position, temps);
    }break;

    case 2: {
        Position[1] += dt * eq_evolution(Position, temps);
        Position[0] += dt * Position[1];
    }break;

    default: throw Erreur("degree EulerCrommer");
    }
}


void Integrable::Newmark (double dt, double temps) {
    switch(degre_eqEvol()) {
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

    default: throw Erreur("Integrable degree Newmark");
    }
}

void Integrable::RungeKutta (double dt, double temps) {
    switch (degre_eqEvol()) {
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
        Vecteur k2 (Position[1] + ((dt*0.5) * k1b));
        std::vector<Vecteur> pk2b = Position;
        pk2b[0] += 0.5 * dt * k1;
        pk2b[1] += 0.5 * dt *k1b;
        Vecteur k2b (eq_evolution (pk2b, temps + dt*0.5));
        Vecteur k3 (Position[1] + ((dt*0.5) * k2b));
        std::vector<Vecteur> pk3b = Position;
        pk3b[0] += 0.5 * dt * k2;
        pk3b[1] += 0.5 * dt *k2b;
        Vecteur k3b (eq_evolution (pk3b, temps + dt*0.5));
        Vecteur k4 (Position[1] + (dt * k3b));
        std::vector<Vecteur> pk4b = Position;
        pk4b[0] += dt * k3;
        pk4b[1] += dt *k3b;
        Vecteur k4b (eq_evolution (pk4b, temps));
	
        Position[0] += ((dt/6) * (k1 + (2*k2) + (2*k3) + k4));
        Position[1] += ((dt/6) * (k1b + (2*k2b) + (2*k3b) + k4b));
        } break;

    default: throw Erreur("Integrable degree RungeKutta");
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
