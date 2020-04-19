QT += core gui opengl widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
CONFIG += c++11

win32:LIBS += -lopengl32


TARGET = ex_05_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    configuration.cc \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    vue_opengl.cc

HEADERS += \
    configuration.h \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/contenu.h

RESOURCES += \
    resource.qrc
