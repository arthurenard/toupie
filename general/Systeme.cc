#include "Systeme.h"

void Systeme::addToupie(std::vector<double> data){
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
    integrateurs.erase(integrateurs.begin() + id -1);
}

Toupie* Systeme::getToupie(size_t nb) const{
    return toupies[nb];
}

int Systeme::getIntegrateur(size_t nb) const{
    return integrateurs[nb];
}


Balle* Systeme::getBalle(size_t nb) const{
    return balles[nb];
}



void Systeme::addBalle(Vecteur P, Vecteur dP){
    balles.push_back(new Balle(P,dP, arrondis(random()) ,arrondis(random()) ,arrondis(random()) ));
}
void Systeme::suppBalle(size_t id){
    delete balles[id];
    balles.erase(balles.begin() + id);
}

double Systeme::random(double min, double max){
    return min + fmod(1./1000. * rand(), max-min);
}
double arrondis(double value) {
     return floor(value + 0.5);
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
        if(trace){
            toupies[i]->recordTrace();
        }
    }
    /*cone->EulerCromer(dt);
    cone2->RungeKutta(dt);
    chinoise->EulerCromer(dt);*/


    for(size_t i(0); i < balles.size(); i++){
        balles[i]->EulerCromer(dt);
        if(balles[i]->ouTof())
            suppBalle(i);
    }

    if(WTF){
        if(balles.size() < 4000){
        for(size_t i(0); i <100; i++){
        addBalle(Vecteur(random(-10.,10.),random(-10.,10.),random(7.,13.)),Vecteur(3));
        }
        }
       // if(balles.size() > 1000)
         //   suppBalle(1);
    }

}
std::vector<double> Systeme::getDataTop(size_t id){
    std::vector<double> data; //type, integrateur, psi, teta, phi, x, y, Dpsi, Dteta, Dphi, Dx, Dy, masse-vo, hauteur, rayon
    data.push_back(toupies[id]->getType());
    data.push_back(integrateurs[id]);
    data.push_back(toupies[id]->get_vect_P()[0]);
    data.push_back(toupies[id]->get_vect_P()[1]);
    data.push_back(toupies[id]->get_vect_P()[2]);
    data.push_back(toupies[id]->get_vect_P()[3]);
    data.push_back(toupies[id]->get_vect_P()[4]);
    data.push_back(toupies[id]->get_vect_dP()[0]);
    data.push_back(toupies[id]->get_vect_dP()[1]);
    data.push_back(toupies[id]->get_vect_dP()[2]);
    data.push_back(toupies[id]->get_vect_dP()[3]);
    data.push_back(toupies[id]->get_vect_dP()[4]);
    data.push_back(toupies[id]->getMV());
    data.push_back(toupies[id]->getHauteur());
    data.push_back(toupies[id]->getRayon());
    return data;
}
std::vector<std::vector<double>> Systeme::getAllData(){
    std::vector<std::vector<double>> data;
    for(size_t i(0); i < toupies.size(); i++){
        data.push_back(getDataTop(i));
    }
    return data;
}
