#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H

//#include "toupies/Toupie.h"
//#include "Systeme.h"

class Systeme;


class SupportADessin
{
    public:
        //constructeur
        virtual ~SupportADessin() {}

        //methode
        virtual void dessine(Systeme const& a_dessiner) = 0; //dessine
};

#endif
