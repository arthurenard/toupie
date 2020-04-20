#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"
using namespace std;

int main()
{
  TextViewer ecran(cout);
  Systeme c(&ecran);

  cout << "Au départ :" << endl;
  c.dessine();

  return 0;
}
