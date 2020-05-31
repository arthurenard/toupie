#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"


void TextViewer::dessine(Systeme const& a_dessiner)
{
    if(a_dessiner.nbToupies() > 0)
    flot << *(a_dessiner.getToupie(0)) << std::endl;

    if(a_dessiner.nbBalles() > 0)
    flot << *(a_dessiner.getBalle(0)) << std::endl;

}
