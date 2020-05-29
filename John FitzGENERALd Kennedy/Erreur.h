#ifndef ERREUR_H
#define ERREUR_H

#include <exception>
#include <iostream>

class Erreur: public std::exception {
    public:
            Erreur(std::string const& phrase="") throw();

            ~Erreur() throw();

             const char* what() const throw();

            void affiche () const throw();

        private:
            std::string m_phrase;            //Description de l'erreur
 };

#endif
