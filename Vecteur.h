#include <iostream> 
#include <vector>
#include <math.h> 
 
 class Vecteur {
	public:
		//methodes
		void augmente (double); //rajoute une dimension avec la veleur passé en argument
		void set_coord (size_t, double); //modifie la n_ieme valeur
		double prod_scal (Vecteur const&) const; //retourne le produit scalaire
		double norme () const; //retourne la norme euclidienne d'un Vecteur 
		double norme2 () const; //retourne le carré de la norme euclidienne d'un Vecteur
		
		//constructeurs
		Vecteur (size_t dimension = 0); //construit un Vecteur nulle de telle dimension
		Vecteur (double, double, double); //construit un Vecteur 3D avec les valeurs passés en argument
		Vecteur (std::vector<double>); //construit un Vecteur avec la liste passé en argument
		
		//operateurs internes
		bool operator== (Vecteur const&) const;
		bool operator!= (Vecteur const&) const;		
		const Vecteur operator- () const; //retourne le vecteur opposé
		const Vecteur operator~ () const; //renvoie le vecteur unitaire
		Vecteur& operator+= (Vecteur const&);
		Vecteur& operator-= (Vecteur const&);		
		Vecteur& operator*= (double scalaire); //multiplie le Vecteur par un scalaire
		Vecteur& operator^= (Vecteur const&); 	
				
		//inutile au beneficiaire de la classe, privilegier les surcharges d'operateur
		Vecteur addition (Vecteur const&) const; //retourne la somme du vecteur passé en argument avec l'instance
		Vecteur soustraction (Vecteur const&) const; //retourne la difference entre le vecteur passé en argument avec l'instance
		Vecteur mult (double) const; //multiplie le vecteur par un double
		void affiche (std::ostream&) const; //utiliser "cout" à la place
		Vecteur prod_vect (Vecteur const&) const; //retourne le produit vectoriel
		Vecteur unitaire () const; //retourn le vecteur unitaire de mm sens et direction
		
	private:
		std::vector<double> vecteur;
};

//operateur externe
const Vecteur operator+ (Vecteur, Vecteur const&);
const Vecteur operator- (Vecteur, Vecteur const&);
const Vecteur operator* (double, Vecteur const&);
const Vecteur operator* (Vecteur const&, double);
const Vecteur operator^ (Vecteur, Vecteur const&); //retourne le produit vectoriel, dimension 3 uniquement
std::ostream& operator<< (std::ostream&, Vecteur const&);
