QT += core gui opengl widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = beyblade_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    glcone.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    glcone.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/Systeme.h

RESOURCES += \
    resource.qrc