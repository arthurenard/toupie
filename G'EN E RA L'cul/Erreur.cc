#include "Erreur.h"
//constructeur
Erreur::Erreur(std::string const& probleme) throw()
    :m_probleme(probleme)
{}

//destructeur
Erreur::~Erreur() throw()
{}

//methodes
const char* Erreur::what() const throw() {
    return m_probleme.c_str();
}

void Erreur::affiche (std::ostream&) const throw() {
    std::cerr << "Erreur: " << this->what() << "\n\n";
}

//operateur externe
std::ostream& operator<<(std::ostream& flux, Erreur const& e) {
    e.affiche(flux);
    return flux;
}
