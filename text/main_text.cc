#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
using namespace std;

int main()
{
  TextViewer ecran(cout);
  Systeme c(&ecran);
  c.addToupie(std::vector<double>{0,0, 0,0.523599,0,0,0, 0,0,60, 0.1,1.5,0.5});
  for(int i(0); i< 20; i++){
      c.dessine();
      c.evolue(0.01);
  }


  return 0;
}
