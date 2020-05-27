#ifndef H_VECTEUR
#define H_VECTEUR

#include <iostream> 
#include <vector>
#include <math.h> 
 
 class Vecteur {
	public:
		//constructeurs
		Vecteur (size_t dimension = 0); //construit un Vecteur nulle de telle dimension
		Vecteur (double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
        Vecteur (double, double, double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
		Vecteur (std::vector<double>); //construit un Vecteur avec la liste passé en argument
	
		//destructeur
	
		//methodes
		void push_back (double); //rajoute une dimension avec la veleur passé en argument
		size_t size() const; //renvoie la dimension du vecteur
		double prod_scal (Vecteur const&) const; //retourne le produit scalaire
		double norme () const; //retourne la norme euclidienne d'un Vecteur 
		double norme2 () const; //retourne le carré de la norme euclidienne d'un Vecteur
        Vecteur projection (Vecteur vect) const; //retourn le Vecteur this projete sur vect
		
		//operateurs internes
		bool operator== (Vecteur const&) const;
		bool operator!= (Vecteur const&) const;	
		const Vecteur operator- () const; //retourne le vecteur opposé
		const Vecteur operator~ () const; //renvoie le vecteur unitaire
		const Vecteur operator+ (Vecteur const&) const;
		const Vecteur operator- (Vecteur const&) const;
		const Vecteur operator* (double scalaire) const;
		const Vecteur operator^ (Vecteur const&) const; //retourne le produit vectoriel, dimension 3 uniquement
		double operator[] (size_t) const;
		double& operator[] (size_t);
		Vecteur& operator+= (Vecteur const&);
		Vecteur& operator-= (Vecteur const&);		
		Vecteur& operator*= (double scalaire); //multiplie le Vecteur par un scalaire
		Vecteur& operator^= (Vecteur const&); 	
				
		//inutile aux beneficiares de la classe
		void affiche (std::ostream&) const; //utiliser "cout" à la place
		
	private:
		std::vector<double> vecteur;
};

//operateur externe
const Vecteur operator* (double, Vecteur const&);
std::ostream& operator<< (std::ostream&, Vecteur const&);

double coplanaire (Vecteur, Vecteur, Vecteur); //retourne (v1 * (v2 ^ v3)) -> = 0 si les 3 vects sont coplanaires

#endif
