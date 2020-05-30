#include "ConeSimple.h"

//constructeurs
ConeSimple::ConeSimple (std::vector<Vecteur> p, double mV, double h, double r, bool move) :
        Cone (p, mV, abs(h), abs(r), move)
{}

//destructeurs

//methodes publiques

Vecteur ConeSimple::eq_evolution (std::vector<Vecteur> p, double) const {
    if (p.size() != degre_Position()) throw Erreur("Cone Simple eq evol");
    Vecteur P = p[0];
    Vecteur dP = p[1];
	Vecteur retour (5);

    	retour[1] = (1/IA1() ) * (MA() + (dP[0] * sin(P[1]) * ( ( (IA1() - I3()) * dP[0] * cos(P[1])) - (I3() * dP[2]))));

    	if(abs(P[1]) < epsilontheta){
        	retour[0]=0.0;
        	retour[2]=0.0;
        	return retour;
    	}

        retour[0] = (dP[1] / (IA1() * sin(P[1]))) * (((I3() - (2 * IA1())) * dP[0] * cos(P[1])) + (I3() * dP[2]));
        retour[2] = (dP[1] / (IA1() * sin(P[1]))) *  ( dP[0] * ( IA1() - ( ( I3() - IA1() ) * cos(P[1]) * cos(P[1]))) - ( I3() * dP[2] * cos(P[1])));
        if(moveXY){
            retour[3]= 0.0;
            retour[4]=0.0;
        }
        else{
        retour[3]= vitesse_G_Rg()[0];
        retour[4]= vitesse_G_Rg()[1];
        }
    return retour;
}

int ConeSimple::getType () const {
    return CONIQUE;
}

//methodes privées
size_t ConeSimple::degre_eqEvol() const {
    return 2;
}
