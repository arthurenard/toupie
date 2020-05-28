#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
using namespace std;

int main()
{
  TextViewer ecran(cout);
  Systeme c(&ecran);

  cout << "Au départ :" << endl;
  for(int i(0); i< 200; i++){
      c.dessine();
      c.evolue(0.05);
  }


  return 0;
}
