
testVecteur : testVecteur.o Vecteur.o
	g++ testVecteur.o Vecteur.o -o testVecteur


Vecteur.o: Vecteur.h Vecteur.cc
	g++ -c Vecteur.cc
	
	
testVecteur.o: testVecteur.cc
	g++ -c testVecteur.cc
	

