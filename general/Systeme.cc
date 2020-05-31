#include "Systeme.h"
//constructeur
Systeme::Systeme(SupportADessin* vue) :
    Dessinable(vue),
    WTF(false),
    toupieFixe(true),
    nyan(new JCC),
    trace(false)
{
    srand (time(NULL));
}

Systeme::~Systeme(){
    clearAll();
}

void Systeme::dessine()
{ support->dessine(*this);}


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

//########################################################################################"

void Systeme::addToupie(Toupie *newtoupie)
{toupies.push_back(newtoupie);}


void Systeme::addToupie(std::vector<double> data){
    integrateurs.push_back(data[1]);
    if(data.size()<13) throw Erreur("Add Toupie erreur declaration");
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

void Systeme::delToupie(size_t nb){
    if(toupies.size() < nb) throw Erreur("delToupie systeme");
    delete toupies[nb - 1];
    toupies.erase(toupies.begin() + nb -1);
    integrateurs.erase(integrateurs.begin() + nb -1);
}

size_t Systeme::nbToupies() const
{return toupies.size(); }

Toupie* Systeme::getToupie(size_t nb) const{
    return toupies[nb];
}

int Systeme::getIntegrateur(size_t nb) const{
    return integrateurs[nb];
}

bool Systeme::getTrace() const
{return trace;}

void Systeme::invertConeFixe(){
    toupieFixe = !toupieFixe;
    for(auto toupie : toupies){
        toupie->invertMoveXY();
    }
}

void Systeme::invertTrace(){
    trace = !trace;
    for(auto toupie: toupies){
    toupie->clearTrace();
    }
}

void Systeme::clearAll(){
    for(auto toupie: toupies){
        delete toupie;
    }
    for(auto balle: balles){
        delete balle;
    }
    delete nyan;
    toupies.clear();
    integrateurs.clear();
    balles.clear();
}

//######################################################################################################################"

void Systeme::addBalle(std::vector<Vecteur> p){
    balles.push_back(new Balle(p, arrondis(random()) ,arrondis(random()) ,arrondis(random()) ));
}

void Systeme::suppBalle(size_t id){
    delete balles[id];
    balles.erase(balles.begin() + id);
}

Balle* Systeme::getBalle(size_t nb) const{
    return balles[nb];
}

size_t Systeme::nbBalles() const
{return balles.size(); }


double Systeme::random(double min, double max){
    return min + fmod(1./1000. * rand(), max-min);
}

//###############################################################################################

void Systeme::partyWTF()
{WTF = true;}
bool Systeme::getWTF() const
{return WTF;}

double Systeme::getNyan() const
{return  nyan->get_vect_P()[2];}



double arrondis(double value) {
     return floor(value + 0.5);
}


std::vector<double> Systeme::getDataTop(size_t id){
    std::vector<double> data; //type, integrateur, psi, teta, phi, x, y, Dpsi, Dteta, Dphi, masse-vo, hauteur, rayon, energietotale
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
        data.push_back(toupies[id]->energie_totale());
        data.push_back(toupies[id]->invariant_vect_rot_Rg3());
        data.push_back(toupies[id]->invariant_moment_cin_A3());
        data.push_back(toupies[id]->invariant_moment_cin_Az());
        data.push_back(toupies[id]->invariant_coplanaires());
    return data;
}
std::vector<std::vector<double>> Systeme::getAllData(){
    std::vector<std::vector<double>> data;
    for(size_t i(0); i < toupies.size(); i++){
        data.push_back(getDataTop(i));
    }
    return data;
}
