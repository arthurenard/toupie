#ifndef DESSINABLE_H
#define DESSINABLE_H

class SupportADessin;

class Dessinable {
    public:
        //constructeur
        Dessinable(SupportADessin* support);

        //destructeur
        virtual ~Dessinable();

        //methode
        virtual void dessine() = 0;

    protected:

    SupportADessin* support;
};

#endif
