#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"


void TextViewer::dessine(Systeme const& a_dessiner)
{
    flot << *(a_dessiner.getChinois()) << std::endl;
   // flot << "Le systeme est composé de " << a_dessiner.toupies.size() << ;

}
