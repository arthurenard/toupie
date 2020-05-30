#include "Systeme.h"

void Systeme::addToupie(std::vector<double> data){
    integrateurs.push_back(data[1]);
    if(data.size()<13) throw "Add Toupie erreur declaration";
    std::vector<Vecteur> p;
    Vecteur P (data[2], data[3], data[4], 0.0, 0.0);
    Vecteur dP (data[7], data[8], data[9], data[5], data[6]);
    p.push_back(P);
    p.push_back(dP);
    if(abs(data[0]) < epsilon)
        addToupie(new ConeSimple(p, data[10], data[11], data[12], toupieFixe));
    if(abs(data[0] - 1) < epsilon)
        addToupie(new ToupieChinoise(p, data[10], data[11], data[12], toupieFixe));
    if(abs(data[0] - 2) < epsilon)
        addToupie(new ToupieG_Conique(p, data[10], data[11], data[12], toupieFixe));
    if(abs(data[0] - 3) < epsilon){
        addToupie(new ConiqueEnergetique(p, data[10], data[11], data[12], toupieFixe));
    }
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

void Systeme::addBalle(std::vector<Vecteur> p){
    balles.push_back(new Balle(p, arrondis(random()) ,arrondis(random()) ,arrondis(random()) ));
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



    for(size_t i(0); i < balles.size(); i++){
        balles[i]->EulerCromer(dt);
        if(balles[i]->ouTof())
            suppBalle(i);
    }

    if(WTF){
        if(balles.size() < 1000){
        for(size_t i(0); i <10; i++){
            std::vector<Vecteur> p;
            Vecteur P (Vecteur(random(-10.,10.),random(-10.,10.),random(7.,13.)));
            Vecteur dP (Vecteur(3));
            p.push_back(P);
            p.push_back(dP);
            addBalle(p);
        }
        }
        nyan->EulerCromer(dt);

    }


}
std::vector<double> Systeme::getDataTop(size_t id){
    std::vector<double> data; //type, integrateur, psi, teta, phi, x, y, Dpsi, Dteta, Dphi, Dx, Dy, masse-vo, hauteur, rayon
        data.push_back(toupies[id]->getType());
        data.push_back(integrateurs[id]);
        data.push_back(toupies[id]->get_vect_P()[0]);
        data.push_back(toupies[id]->get_vect_P()[1]);
        data.push_back(toupies[id]->get_vect_P()[2]);
        data.push_back(toupies[id]->get_vect_dP()[3]);
        data.push_back(toupies[id]->get_vect_dP()[4]);
        data.push_back(toupies[id]->get_vect_dP()[0]);
        data.push_back(toupies[id]->get_vect_dP()[1]);
        data.push_back(toupies[id]->get_vect_dP()[2]);
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
