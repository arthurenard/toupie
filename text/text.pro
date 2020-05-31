CONFIG += c++11

TARGET = beyblade_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    text_viewer.cc\
    ../general/bases/testVecteur.cc\
    ../general/bases/testMatrice33.cc



HEADERS += \
    ../general/Systeme.h \
    text_viewer.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/bases/testVecteur.h\
    ../general/bases/testMatrice33.h



