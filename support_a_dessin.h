#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H

#include "Toupie.h"

class SupportADessin
{
 public:
  virtual ~SupportADessin() {}

  virtual void dessine(Toupie const& a_dessiner) = 0;


};

#endif
