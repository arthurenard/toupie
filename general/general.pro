TEMPLATE = lib

CONFIG += staticlib c++11

SOURCES += Systeme.cc \
    bases/Vecteur.cc \
    bases/Matrice33.cc \
    bases/constantes.cc \
    jcc.cc \
    toupies/ConiqueEnergetique.cc \
    toupies/Toupie.cc \
    toupies/Cone.cc \
    toupies/ToupieChinoise.cc \
    toupies/ConeSimple.cc \
    Integrable.cc \
    Balle.cc \
    Memoire.cc\
    toupies/ToupieG_Conique.cc

HEADERS += \
    Systeme.h \
    bases/Vecteur.h \
    bases/Matrice33.h \
    bases/constantes.h \
    jcc.h \
    toupies/ConiqueEnergetique.h \
    toupies/Toupie.h \
    toupies/ToupieChinoise.h \
    toupies/ConeSimple.h \
    toupies/Cone.h \
    dessinable.h \
    support_a_dessin.h \
    Integrable.h\
    Balle.h \
    Memoire.h\
    toupies/ToupieG_Conique.h
