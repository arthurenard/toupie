#include "Erreur.h"
Erreur::Erreur(std::string const& probleme) throw()
    :m_phrase(probleme)
{}

const char* Erreur::what() const throw() {
    return m_phrase.c_str();
}

void Erreur::affiche () const throw() {
    std::cerr << "Erreur: " << this->what() << "\n\n";
}

Erreur::~Erreur() throw()
{}
