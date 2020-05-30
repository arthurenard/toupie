#ifndef ERREUR_H
#define ERREUR_H

#include <exception>
#include <iostream>

class Erreur: public std::exception {
    public:
        //constructeur
        Erreur(std::string const& probleme="") throw();

        //destructeur
        ~Erreur() throw();

        //methodes
        const char* what() const throw();

        //methode inutile au beneficiaire
        void affiche (std::ostream&) const throw(); //affiche le vecteur mais c'est mieux d'utiliser <<

    private:
        //attributs
        std::string m_probleme; //le message d'erreur catché
 };
std::ostream& operator<< (std::ostream&, Erreur const&); //affiche l'erreur

#endif
