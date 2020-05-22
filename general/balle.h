#ifndef BALLE_H
#define BALLE_H
#include <iostream>
#include <vector>

#include "bases/Vecteur.h"
#include "Integrable.h"

class Balle :  public Integrable
{
public:
    Balle(Vecteur P, Vecteur dP, double r, double v, double b);


    virtual void EulerCromer(double pas_de_temps, double temps = 0) override;

    virtual Vecteur eq_evolution (Vecteur P, Vecteur dP, double temps = 0) override;

    double getRayon(){return rayon;}
    std::vector<double> getRVB(){return rvb;}
    bool ouTof(){
        if(abs(vect_P[0]) > 10 || abs(vect_P[1]) > 10 )
            return true;
        return false;
    }

private:
    double rayon, coefRest;
    std::vector<double>rvb;

};

#endif // BALLE_H

