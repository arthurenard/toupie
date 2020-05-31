#include "testVecteur.h"

void testVecteur(){
	
	
	//Test initialisation + affichage
	Vecteur vect1(1.0, 2.0, -0.1);
	Vecteur vect2(2.6, 3.5,  4.1);
	Vecteur vect3;
    std::cout << "Vecteur 1 : ";
    std::cout << vect1 << std::endl;

    std::cout << "Vecteur 2 : ";
    std::cout << vect2 << std::endl;
	
    std::cout << "Vecteur 3 : ";
    std::cout << vect3 << std::endl;



	//Test Copie
	vect3 = vect1;
    std::cout << "Vecteur 3 : ";
    std::cout << vect3 << std::endl;


	
	
	//Test ine/egalite 
    std::cout << "Le vecteur 1 est ";
	if (vect1 == vect2) {
        std::cout << "égal au";
	} else {
        std::cout << "différent du";
	}
    std::cout << " vecteur 2," << std::endl << "et est ";
	if (vect1 != vect3) {
        std::cout << "différent du";
	} else {
        std::cout << "égal au";
	}
    std::cout << " vecteur 3" << std::endl;
	
	//Test operations
    std::cout << vect1 << " + " << vect2 << " = " << vect1 + vect2 << std::endl;
    std::cout << " - " << vect2 << " = " << -vect2 << std::endl;
    std::cout << vect1 << " - " << vect2 << " = " << vect1 - vect2 << std::endl;
    std::cout << "3.5 * " << vect2 << " = " << (3.5*vect2) << std::endl;
    std::cout << vect1 << " * " << vect2 << " = " << vect1.prod_scal(vect2) << std::endl;
	vect3 = vect1^vect2;
    std::cout << vect1 << " ^ " << vect2 << " = " << vect3 << std::endl;
    std::cout << "| " << vect1 << " | = " << vect1.norme() << std::endl;
    std::cout << "| " << vect1 << " |² = " << vect1.norme2() << std::endl;
	
    std::cout << (vect1 *= 2.0) << std::endl;
	
	getchar();
}
