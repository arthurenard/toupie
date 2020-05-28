all: testMatrice testVecteur


testMatrice : testMatrice33.o Matrice33.o Vecteur.o
	g++ testMatrice33.o Matrice33.o Vecteur.o -o testMatrice33 -std=c++11
	
testVecteur : testVecteur.o Vecteur.o
	g++ testVecteur.o Vecteur.o -o testVecteur -std=c++11
	


Vecteur.o: Vecteur.cc
	g++ -c Vecteur.cc -std=c++11
	
Matrice33.o: Matrice33.cc 
	g++ -c Matrice33.cc -std=c++11
	
	
	
	
testVecteur.o: testVecteur.cc
	g++ -c testVecteur.cc -std=c++11
	
testMatrice33.o: testMatrice33.cc Matrice33.h
	g++  -c testMatrice33.cc -std=c++11
	


