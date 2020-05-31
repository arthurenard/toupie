#ifndef BALLE_H
#define BALLE_H
#include <iostream>
#include <vector>

#include "bases/Vecteur.h"
#include "Integrable.h"

class Balle :  public Integrable
{
public:
    //constructeur
    Balle(std::vector<Vecteur> Position, double rouge, double vert, double bleu);

    //destructeur
    ~Balle() = default;

    //methodes
    virtual void EulerCromer(double pas_de_temps, double temps = 0) override; //adapte la position et les vitesses en cas de rebond

    virtual Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) const override;

    double getRayon(); //retourne le rayon
    std::vector<double> getRVB(); //renvoie l'attribut rvb
    bool ouTof(); //si la balle est sortie de l'arène

protected:
    double rayon; //le rayon
    double coefRest; //le coeffecient de restitution lors d'un rebond
    std::vector<double>rvb; //renvoie les composantes Rouge Vert Bleu
    size_t degre_Position () const override; //la taille du vector Position
    size_t degre_eqEvol() const override; //le degre des equations d'evolution
};

#endif // BALLE_H

