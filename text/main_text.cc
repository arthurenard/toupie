#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
#include "../general/bases/Vecteur.h"
#include "../general/bases/testVecteur.h"
#include "../general/bases/testMatrice33.h"

using namespace std;

void testToupie();
void testIntegrateur();

int main()
{
    //Decommentez le test que vous souhaitez realiser

  //testVecteur();
  //testMatrice();
  //testIntegrateur(); //Exactement les memes valeurs que le prof jusqu'au rebond (z=0.5)
  //testToupie();   //Exactement les memes valeurs que le prof

  return 0;
}

void testToupie(){
    TextViewer ecran(cout);
    Systeme systeme(&ecran);
    systeme.addToupie(std::vector<double>{0,0, 0,0.523599,0,0,0, 0,0,60, 0.1,1.5,0.5});
    for(int i(0); i< 20; i++){
        systeme.dessine();
        systeme.evolue(0.01);
    }
}

void testIntegrateur(){
    TextViewer ecran(cout);
    Systeme systeme(&ecran);

    systeme.addBalle(std::vector<Vecteur>{Vecteur(0.0, 0.0, 1.0), Vecteur(0.0, 0.0, 2.0)});
    for(int i(0); i< 69; i++){
        systeme.dessine();
        systeme.evolue(0.01);
    }
}
