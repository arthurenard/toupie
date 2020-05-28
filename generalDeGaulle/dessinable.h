#ifndef DESSINABLE_H
#define DESSINABLE_H

class SupportADessin;

class Dessinable {
 public:
  Dessinable(SupportADessin* support)
    : support(support)
  {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

 protected:

  SupportADessin* support;
};

#endif
