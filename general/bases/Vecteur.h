#ifndef H_VECTEUR
#define H_VECTEUR

#include <iostream> 
#include <vector>
#include <math.h> 

#include "Erreur.h"
 
 class Vecteur {
	public:
		//constructeurs
		Vecteur (size_t dimension = 0); //construit un Vecteur nulle de telle dimension
		Vecteur (double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
        Vecteur (double, double, double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
		Vecteur (std::vector<double>); //construit un Vecteur avec la liste passé en argument
	
		//destructeur
	
		//methodes
        void push_back (double = 0.); //rajoute une dimension avec la veleur passé en argument
		size_t size() const; //renvoie la dimension du vecteur
		double prod_scal (Vecteur const&) const; //retourne le produit scalaire
		double norme () const; //retourne la norme euclidienne d'un Vecteur 
		double norme2 () const; //retourne le carré de la norme euclidienne d'un Vecteur
        Vecteur projection (Vecteur vect) const; //retourn le Vecteur this projete sur vect
		
		//operateurs internes
        bool operator== (Vecteur const&) const; //retourne true si toutes les composantes et le dim sont identiques, faux sinon
        bool operator!= (Vecteur const&) const;	//retourne l'opposé de ==
		const Vecteur operator- () const; //retourne le vecteur opposé
        const Vecteur operator~ () const; //retourne le vecteur unitaire
        const Vecteur operator+ (Vecteur const&) const; //retourne la somme de deux vecteurs de même dimension, lance une erreur sinon
        const Vecteur operator- (Vecteur const&) const; //retourne la différence de deux vecteurs de même dimension, lance une erreur sinon
        const Vecteur operator* (double scalaire) const; //retourne le produit usuel entre un réel et un vecteur
        const Vecteur operator^ (Vecteur const&) const; //retourne le produit vectoriel, dimension 3 uniquement, lance erreur sinon
        double operator[] (size_t) const; //retourne la ieme - 1 composante passée en parametre
        double& operator[] (size_t); //permet de modifier la ième - 1 composante passée en parametre
        Vecteur& operator+= (Vecteur const&); //affecte la somme de deux vecteurs de meme dimension, lance une erreur sinon
        Vecteur& operator-= (Vecteur const&); //affecte la difference de deux vecteurs de meme dimension, lance une erreur sinon
		Vecteur& operator*= (double scalaire); //multiplie le Vecteur par un scalaire
        Vecteur& operator^= (Vecteur const&); //assigne le produit vectoriel, lance une erreur sinon
				
		//inutile aux beneficiares de la classe
        void affiche (std::ostream&) const; //utiliser << à la place
		
	private:
		std::vector<double> vecteur;
};

//operateurs externes
const Vecteur operator* (double, Vecteur const&); //retourne le produit entre un vecteur et un reel
std::ostream& operator<< (std::ostream&, Vecteur const&); //affiche un vecteur

double coplanaire (Vecteur, Vecteur, Vecteur); //retourne (v1 * (v2 ^ v3)) -> = 0 si les 3 vects sont coplanaires

#endif
