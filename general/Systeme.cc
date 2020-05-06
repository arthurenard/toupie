#include "Systeme.h"

void Systeme::addToupie(std::vector<double> data){
    types.push_back(data[0]);
    integrateurs.push_back(data[1]);
    if(data.size()<15) throw "Add Toupie erreur declaration";

    Vecteur P(data[2], data[3], data[4], data[5], data[6]), dP(data[7], data[8], data[9], data[10], data[11]);
    if(abs(data[0]) < epsilon)
        addToupie(new ConeSimple(P, dP, data[12], data[13], data[14]));
    if(abs(data[0] - 1) < epsilon)
        addToupie(new ToupieChinoise(P, dP, data[12], data[13], data[14]));
}

void Systeme::delToupie(size_t id){
    toupies.erase(toupies.begin() + id -1);
    types.erase(types.begin() + id -1);
    integrateurs.erase(integrateurs.begin() + id -1);
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
