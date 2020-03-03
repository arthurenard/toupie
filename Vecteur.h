#include <iostream> 
#include <vector>
#include <math.h> 
 
 class Vecteur {
	public:
		void augmente (double); //rajoute une dimension avec la veleur passé en argument
		void set_coord (size_t, double); //modifie la n_ieme valeur
		void affiche (std::ostream&) const; //utiliser "cout" à la place
		Vecteur addition (Vecteur const&) const; //retourne la somme du vecteur passé en argument avec l'instance
		Vecteur oppose () const; //retourne le vecteur opposé
		Vecteur soustraction (Vecteur const&) const; //retourne la difference entre le vecteur passé en argument avec l'instance
		Vecteur mult(double) const; //multiplie le vecteur par un double
		double prod_scal(Vecteur const&) const; //retourne le produit scalaire
		Vecteur prod_vect(Vecteur const&) const; //retourne le produit vectoriel
		double norme () const; //retourne la norme euclidienne d'un Vecteur 
		double norme2 () const; //retourne le carré de la norme euclidienne d'un Vecteur
		
		//operateur interne
		bool operator==(Vecteur const&) const;
		bool operator!=(Vecteur const&) const;		
		
		//constructeur
		Vecteur (size_t dimension = 0); //construit un Vecteur nulle de telle dimension
		Vecteur (double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
		Vecteur (std::vector<double>); //construit un Vecteur avec la liste passé en argument
		
	private:
		std::vector<double> vecteur;
};

//operateur externe
std::ostream& operator<<(std::ostream&, Vecteur const&);
