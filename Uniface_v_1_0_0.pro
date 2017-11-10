#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T18:38:53
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Uniface_v_1_0_0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileworker.cpp \
    globalvariables.cpp \
    bytebutton.cpp \
    controlbasegraphobject.cpp \
    levelcontrol.cpp \
    uniface.cpp

HEADERS  += mainwindow.h \
    universalfactory.h \
    fileworker.h \
    globalvariables.h \
    globalvarfromresourcesloader.h \
    bytebutton.h \
    controlbasegraphobject.h \
    levelcontrol.h \
    uniface.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
