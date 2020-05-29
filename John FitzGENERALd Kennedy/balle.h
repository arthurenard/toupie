#ifndef BALLE_H
#define BALLE_H
#include <iostream>
#include <vector>

#include "bases/Vecteur.h"
#include "Integrable.h"

class Balle :  public Integrable
{
public:
    Balle(std::vector<Vecteur>, double r, double v, double b);

    virtual void EulerCromer(double pas_de_temps, double temps = 0) override;

    virtual Vecteur eq_evolution (std::vector<Vecteur>, double temps = 0) override;

    double getRayon(){return rayon;}
    std::vector<double> getRVB(){return rvb;}
    bool ouTof(){
        if(abs(Position[0][0]) > 10 || abs(Position[0][1]) > 10 )
            return true;
        return false;
    }

protected:
    double rayon, coefRest;
    std::vector<double>rvb;
    size_t degre_Position () const override;
    size_t degre_eqEvol() const override;
};

#endif // BALLE_H

