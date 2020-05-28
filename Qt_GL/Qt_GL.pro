QT += core gui opengl widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = beyblade

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    addtoupie.cc \
    glchinoise.cc \
    information.cc \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    glcone.cc \
    mainwindow.cc \
    sauvegarde.cc \
    vue_opengl.cc

HEADERS += \
    addtoupie.h \
    glchinoise.h \
    glwidget.h \
    information.h \
    mainwindow.h \
    sauvegarde.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    glcone.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/Systeme.h
    ../general/bases/constantes.h

RESOURCES += \
    resource.qrc
