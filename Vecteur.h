#include <iostream> 
#include <vector>
#include <math.h> 
 
 class Vecteur {
	public:
		void augmente (double);
		void set_coord (size_t, double);
		void affiche () const;
		bool compare (Vecteur const&);
		Vecteur addition (Vecteur const&) const;
		Vecteur oppose () const;
		Vecteur soustraction (Vecteur const&) const;
		Vecteur mult(double) const;
		double prod_scal(Vecteur const&) const;
		Vecteur prod_vect(Vecteur const&) const;
		double norme () const;
		double norme2 () const;
		
	private:
		std::vector<double> vecteur;
};
