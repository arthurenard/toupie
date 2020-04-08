
testVecteur : testVecteur.o Vecteur.o
	g++ testVecteur.o Vecteur.o -o testVecteur
	
testMatrice : testMatrice33.o Matrice33.o
	g++ testMatrice33.o Matrice33.o -o testMatrice33




Vecteur.o: Vecteur.h Vecteur.cc
	g++ -c Vecteur.cc
	
Matrice33.o: Matrice33.h Matrice33.cc
	g++ -std=c++11 -c Matrice33.cc 
	
	
	
	
testVecteur.o: testVecteur.cc
	g++ -c testVecteur.cc
	
testMatrice33.o: testMatrice33.cc
	g++ -c testMatrice33.cc
	

