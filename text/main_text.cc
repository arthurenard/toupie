#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
using namespace std;

int main()
{
  TextViewer ecran(cout);
  Systeme c(&ecran);

  cout << "Au départ :" << endl;
  for(int i(0); i< 20; i++){
      c.dessine();
      c.evolue(0.01);
  }


  return 0;
}
