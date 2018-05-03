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


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/fileworker.cpp \
    src/globalvariables.cpp \
    src/bytebutton.cpp \
    src/controlbasegraphobject.cpp \
    src/levelcontrol.cpp \
    src/uniface.cpp

HEADERS  += src/mainwindow.h \
    src/universalfactory.h \
    src/fileworker.h \
    src/globalvariables.h \
    src/globalvarfromresourcesloader.h \
    src/bytebutton.h \
    src/controlbasegraphobject.h \
    src/levelcontrol.h \
    src/uniface.h\
    src/swenum.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
