#include "testMatrice33.h"

void testMatrice3(){
	

	Matrice33 I;
	Matrice33 diag(1., 2., 3.);
	Matrice33 mat(1.1, 1.2, 1.3,
				  2.1, 2.2, 2.3,
				  3.1, 3.2, 3.3);
	Matrice33 mat2(1., 2., 0.,
				   3., 4., 0,
				   0., 0., 1.);
	Vecteur v(5.5, 6.6, 7.7);
        std::cout << I << std::endl << diag << std::endl;
        std::cout << I.det() << " "
		<< diag.det() << " "
		<< mat.det() << " "
        << mat2.det() << std::endl;
        std::cout << I.inv() << std::endl << diag.inv() << std::endl << mat.inv() << std::endl << mat2.inv() << std::endl;

        std::cout << mat + mat << std::endl;
        std::cout << mat - mat << std::endl;
        std::cout << diag-I << std::endl;
        std::cout << 4.4 * diag << std::endl;
        std::cout << 2. * mat << std::endl;
        std::cout << mat * v << std::endl;
        std::cout << mat * mat << std::endl;
        std::cout << mat2 * mat2.inv() << std::endl;
        std::cout << mat.transp() << std::endl;
}
