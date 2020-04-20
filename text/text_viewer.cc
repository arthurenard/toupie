#include <iostream>
#include "text_viewer.h"

void TextViewer::dessine(Systeme const& a_dessiner)
{
    flot << a_dessiner.getToupie(0) << std::endl;
   // flot << "Le systeme est composé de " << a_dessiner.toupies.size() << ;
  //flot << "Planete1 : x " << a_dessiner.getPlanete1X() << "  y "  << a_dessiner.getPlanete1Y() << std::endl;
  //flot << "Planete2 : x " << a_dessiner.getPlanete2X() << "  y "  << a_dessiner.getPlanete2Y() << std::endl;
}
