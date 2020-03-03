#include <iostream> 
#include <vector>
#include <math.h> 
 
 class Vecteur {
	public:
		void augmente (double);
		void set_coord (size_t, double);
		void affiche (std::ostream&) const;
		Vecteur addition (Vecteur const&) const;
		Vecteur oppose () const;
		Vecteur soustraction (Vecteur const&) const;
		Vecteur mult(double) const;
		double prod_scal(Vecteur const&) const;
		Vecteur prod_vect(Vecteur const&) const;
		double norme () const;
		double norme2 () const;
		
		//operateur
		bool operator==(Vecteur const&) const;
		bool operator!=(Vecteur const&) const;		
		
		//constructeur
		Vecteur (size_t = 0);
		Vecteur (double, double, double);
		Vecteur (std::vector<double>);
		
	private:
		std::vector<double> vecteur;
};

std::ostream& operator<<(std::ostream&, Vecteur const&);
