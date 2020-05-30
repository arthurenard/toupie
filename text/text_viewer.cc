#include <iostream>
#include "text_viewer.h"
#include "Systeme.h"


void TextViewer::dessine(Systeme const& a_dessiner)
{

    flot << *(a_dessiner.getToupie(0)) << std::endl;
}
