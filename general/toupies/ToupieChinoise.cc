#include "ToupieChinoise.h"

//constructeurs

ToupieChinoise::ToupieChinoise (std::vector<Vecteur> p, double mV, double h, double r, bool move) :
        Toupie (p, abs(mV), abs(h), abs(r), move)
{
    if (p.size() != 2) throw Erreur("ToupieChinoise degree");
}

//destructeurs

//methodes publiques
Vecteur ToupieChinoise::eq_evolution (std::vector<Vecteur> p, double) const {
    if (p.size() != degre_Position()) throw Erreur("ToupieChinoise eq evol");
    double theta(p[0][1]);
            double dPsi(p[1][0]), dTheta(p[1][1]), dPhi(p[1][2]);
            double r (rayon), m(masse()), a(alpha());
            Vecteur retour (5);


            double f1 (dPhi + (dPsi * cos(theta)));
            double f3 ((I1() * I3()) + (m * I1() * pow(sin(theta) * r, 2)) + (m * I3() * pow(r * (a - cos(theta)), 2)));
            double f2 ((dTheta * f1 * I3() * (I3() + (m * r * r * (1 - (a * cos(theta)))))/(f3 * sin(theta))) - (2 * dPsi * dTheta / tan(theta)));

            if(fmod(abs(theta), pi) < 0.01){
                f2 = 0.0;
            }
            retour[0] = f2;

            retour[1] = (sin(theta) / (I1() + m *r*r*(pow(a - cos(theta), 2) + sin(theta) * sin(theta)))) *
                    (dPsi * dPsi * (m * r * r * (cos(theta) - a) * (1 - a*cos(theta)) + I1() * cos(theta)) +
                     f1 * dPsi * ( m * r * r * (a * cos(theta) - 1) - I3()) - m * a * pow(r * dTheta, 2) - m * r * a * g);



            retour[2] = dPsi * dTheta * sin(theta) - cos(theta) * f2 -
                    f1 * dTheta * sin(theta) * m * r * r * (I3() * (a - cos(theta)) + I1() * cos(theta)) / f3;



        if(moveXY){
            retour[3]= 0.0;
            retour[4]=0.0;
        }
        else{
            retour[3]= rayon * ( (Position[1][1] * sin(Position[0][0]) ) - (Position[1][2] * cos(Position[0][0]) * sin(Position[0][1])));
            retour[4]= (- rayon) * (Position[1][1] * cos(Position[0][0]) + (Position[1][2] * sin(Position[0][0]) * sin(Position[0][1])));
        }
	
	return retour;
}

//methodes privées
double ToupieChinoise::volume () const {
	double r (rayon), h (hauteur);
	return pi * (((4.0/3) * pow(r, 3)) - (pow(h, 2) * (r - ((1.0/3) * h)))); // p9
}

double ToupieChinoise::alpha() const {
	double r (rayon), h (hauteur);
	return (0.75 * h * h) / ((r + h) * r);
}

double ToupieChinoise::I1 () const {
	double r (rayon), h (hauteur);
    	return (0.5 * I3()) + (pi * (1.0/15.) * masseVolumique * pow((2*r) - h, 2) * (pow(r, 3) + (h*r*r) - (3*h*h*r) + 3 * pow(h, 3))) - (masse() * pow(r * alpha(), 2)); // p9
}

double ToupieChinoise::I3 () const {
	double r (rayon), h (hauteur);
    	return pi * (1.0/30.) * masseVolumique * pow((2*r) - h, 3) * (2 * pow(r, 2) + (3 * h * r) + (3 * pow(h, 2))); // p9
}

Vecteur ToupieChinoise::OG () const {
        return (rayon * (1 - alpha()) * OG_unitaire());
}
int ToupieChinoise::getType() const {
    return CHINOISE;
}

size_t ToupieChinoise::degre_eqEvol() const {
    return 2;
}

//operateurs internes

//methodes inutiles aux beneficiaires de la classe


//operateurs externes
