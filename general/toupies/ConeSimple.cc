#include "ConeSimple.h"

//constructeurs
ConeSimple::ConeSimple (std::vector<Vecteur> p, double mV, double h, double r) :
        Cone (p, degre(), mV, abs(h), abs(r))
{}

//destructeurs

//methodes publiques

Vecteur ConeSimple::eq_evolution (std::vector<Vecteur> p, double) {
    if (p.size() != degre()) throw "Cone Simple eq evol";
    Vecteur P = p[0];
    Vecteur dP = p[1];
	Vecteur retour (5);

    	retour[1] = (1/IA1() ) * (MA() + (dP[0] * sin(P[1]) * ( ( (IA1() - I3()) * dP[0] * cos(P[1])) - (I3() * dP[2]))));

    	if(abs(P[1]) < epsilontheta){
        	retour[0]=0.0;
        	retour[2]=0.0;
        	return retour;
    	}

    	retour[0] = (P[1] / (IA1() * sin(P[1]))) * (((I3() - (2 * IA1())) * dP[0] * cos(P[1])) + (I3() * dP[2]));
        retour[2] = (dP[1] / (IA1() * sin(P[1]))) *  ( dP[0] * ( IA1() - ( ( I3() - IA1() ) * cos(P[1]) * cos(P[1]))) - ( I3() * dP[2] * cos(P[1])));


        return retour;
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe

int ConeSimple::getType(){return CONIQUE;}
//operateurs externes

size_t ConeSimple::degre () const {
    return 2;
}

