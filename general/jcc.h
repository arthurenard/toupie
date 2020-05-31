#ifndef JCC_H
#define JCC_H
#include "balle.h"

class JCC : public Balle {
    public:
        //constructeur
        JCC();
        virtual ~JCC() = default;

        //methode
        Vecteur eq_evolution(std::vector<Vecteur>, double temps = 0) const override; //renvoie le vecteur vect_g avec un coefficient d'amortissement
};

#endif
