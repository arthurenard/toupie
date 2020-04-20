TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES += Systeme.cc \
    bases/Vecteur.cc \
    bases/Matrice33.cc \
    bases/constantes.cc \
    toupies/Toupie.cc \
    toupies/ToupieChinoise.cc \
    toupies/ConeSimple.cc \

HEADERS += \
    Systeme.h \
    bases/Vecteur.h \
    bases/Matrice33.h \
    bases/constantes.h \
    toupies/Toupie.h \
    toupies/ToupieChinoise.h \
    toupies/ConeSimple.h \
    dessinable.h \
    support_a_dessin.h
