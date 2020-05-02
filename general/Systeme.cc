#include "Systeme.h"

void Systeme::addToupie(int type, int integrateur, std::vector<double> data){
    types.push_back(type);
    integrateurs.push_back(integrateur);
    if(data.size()<13) throw "Add Toupie erreur declaration";

    Vecteur P(data[0], data[1], data[2], data[3], data[4]), dP(data[5], data[6], data[7], data[8], data[9]);
    if(type == 0)
        addToupie(new ConeSimple(P, dP, data[10], data[11], data[12]));
    if(type == 1)
        addToupie(new ToupieChinoise(P, dP, data[10], data[11], data[12]));
}


Toupie* Systeme::getToupie(size_t nb) const{
    return toupies[nb];
}
int Systeme::getType(size_t nb) const{
    return types[nb];
}
int Systeme::getIntegrateur(size_t nb) const{
    return integrateurs[nb];
}



void Systeme::evolue(double dt){
    for(size_t i(0); i < toupies.size(); i++){
        switch (integrateurs[i]) {
        case 0:
                toupies[i]->EulerCromer(dt);
            break;
        case 1:
            toupies[i]->Newmark(dt);
            break;
        case 2:
            toupies[i]->RungeKutta(dt);
            break;
        default:
            toupies[i]->EulerCromer(dt);
            break;
        }
    }
    /*cone->EulerCromer(dt);
    cone2->RungeKutta(dt);
    chinoise->EulerCromer(dt);*/
}
