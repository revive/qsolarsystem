#-------------------------------------------------
#
# Project created by QtCreator 2012-11-01T13:55:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT      += opengl

TARGET = qsolorsystem
TEMPLATE = app


SOURCES += main.cpp\
        swidget.cpp \
    sglwidget.cpp \
    ssphere3d.cpp

HEADERS  += swidget.h \
    sglwidget.h \
    ssphere3d.h

FORMS    += swidget.ui

OTHER_FILES += \
    simple.vert \
    simple.frag

RESOURCES += \
    resource.qrc
