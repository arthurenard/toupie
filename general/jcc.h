#ifndef JCC_H
#define JCC_H
#include "balle.h"

class JCC : public Balle
{
public:
    JCC();
    Vecteur eq_evolution(std::vector<Vecteur>, double temps = 0) override;
};

#endif // JCC_H
