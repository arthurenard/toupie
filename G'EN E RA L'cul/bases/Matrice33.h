
#ifndef H_MATRICE33
#define H_MATRICE33

#include <iostream> 
#include <array>
#include <cmath>
#include "Vecteur.h"
#include "Erreur.h"
#include "constantes.h"

class Matrice33 {
	public:
		//constructeurs
        Matrice33 (double = 1., double = 1., double = 1.); //constructeur de matrice diagonale, matrice identité par défaut
		Matrice33 (double, double, double, double, double, double, double, double, double); //construit la matrice ligne par ligne
		
		//destructeur
		
		//methodes
        const Matrice33 transp() const; //renvoie la transposé de la matrice
        const Matrice33 inv () const; //renvoie l'inverse de la matrice
        double det() const; //renvoie le déterminant de la matrice
		
		//operateurs internes
        bool operator== (Matrice33 const&) const; //comprare chaque case la matrice et renvoie bool si tout est identique
        bool operator!= (Matrice33 const&) const; //renvoie
		const Matrice33 operator- () const; //retourne la matrice opposée
        const Matrice33 operator+ (Matrice33 const&) const; //retourne la somme usuelle de 2 matrices
        const Matrice33 operator- (Matrice33 const&) const; //retourne la différence usuelle de 2 matrices
        const Matrice33 operator* (Matrice33 const&) const; //retourne le produit usuel de 2 matrices
        const Matrice33 operator* (double) const; //retourne le produit usuel entre un reel et une matrice
        Matrice33& operator+= (Matrice33 const&); //assignne la somme usuelle des deux matrices
        Matrice33& operator-= (Matrice33 const&); //assigne la différence usuelle de deux matrices
        Matrice33& operator*= (Matrice33 const&); //assigne le produit usuel de deux matrices
        Matrice33& operator*= (double scalaire); //assigne le produit usuel entre un réel et une matrice
		
        Vecteur operator* (Vecteur const&) const; //retourne le produit usuel entre une matrice et un vecteur
		
		//inutile aux beneficiares de la classe
        void affiche (std::ostream&) const; //affiche la matrice ligne par ligne
		
	private:
        //atributs
        std::array<std::array<double, 3>, 3> matrice; //un array de dim 3 d'array de dim 3 pour représenter la matrice 3x3
		
		//methodes privees
};

//operateurs externes
const Matrice33 operator* (double, Matrice33 const&); //retourne le produit usuel entre une matrice et un reel (dans cet ordre)
std::ostream& operator<< (std::ostream&, Matrice33 const&); //affiche la matrice ligne par ligne

#endif
