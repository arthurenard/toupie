
#include <iostream>
#include "Vecteur.h"

using namespace std;

int main(){
	
	
	//Test initialisation + affichage
	Vecteur vect1(1.0, 2.0, -0.1);
	Vecteur vect2(2.6, 3.5,  4.1);
	Vecteur vect3;
	cout << "Vecteur 1 : ";
	cout << vect1 << endl;

	cout << "Vecteur 2 : ";
	cout << vect2 << endl;
	
	cout << "Vecteur 3 : ";
	cout << vect3 << endl;



	//Test Copie
	vect3 = vect1;
	cout << "Vecteur 3 : ";
	cout << vect3 << endl;


	
	
	//Test ine/egalite 
	cout << "Le vecteur 1 est ";
	if (vect1 == vect2) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est ";
	if (vect1 != vect3) {
		cout << "différent du";
	} else {
		cout << "égal au";
	}
	cout << " vecteur 3" << endl;
	
	//Test operations
	cout << vect1 << " + " << vect2 << " = " << vect1 + vect2 << endl;
	cout << " - " << vect2 << " = " << -vect2 << endl;
	cout << vect1 << " - " << vect2 << " = " << vect1 - vect2 << endl;
	cout << "3.5 * " << vect2 << " = " << (3.5*vect2) << endl;
	cout << vect1 << " * " << vect2 << " = " << vect1.prod_scal(vect2) << endl;
	vect3 = vect1^vect2;
	cout << vect1 << " ^ " << vect2 << " = " << vect3 << endl;
	cout << "| " << vect1 << " | = " << vect1.norme() << endl;
	cout << "| " << vect1 << " |² = " << vect1.norme2() << endl;
	
	cout << (vect1 *= 2.0) <<endl;
	
	
	
	
	getchar();
}
