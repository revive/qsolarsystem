#-------------------------------------------------
#
# Project created by QtCreator 2012-11-01T13:55:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT      += opengl

TARGET = qsolarsystem
TEMPLATE = app


SOURCES += main.cpp\
        swidget.cpp \
    sglwidget.cpp \
    ssphere3d.cpp \
    sutils.cpp

HEADERS  += swidget.h \
    sglwidget.h \
    ssphere3d.h \
    sutils.h

FORMS    += swidget.ui

OTHER_FILES += \
    simple.vert \
    simple.frag \
    pic/t1.png \
    model/sphere.obj \
    model/sphere.frag \
    model/sphere.vert \
    pic/wm.png

RESOURCES += \
    resource.qrc
