#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H

//#include "toupies/Toupie.h"
//#include "Systeme.h"

class Systeme;


class SupportADessin
{
 public:
  virtual ~SupportADessin() {}

  virtual void dessine(Systeme const& a_dessiner) = 0;

};

#endif
