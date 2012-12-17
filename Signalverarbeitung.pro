#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T20:07:06
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Signalverarbeitung
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x
#QMAKE_LFLAGS += -lfftw3
LIBS += /usr/lib/libfftw3.a

TEMPLATE = app

SOURCES += main.cpp \
    signalprocdispatcher.cpp \
    networkdriver.cpp \
    signalprocworker.cpp \
    abstractcalc.cpp \
    xcorrcalc.cpp \
    oscidriver.cpp \
    vxi11/vxi11_user.cc \
    vxi11/vxi11_clnt.c \
    vxi11/vxi11_xdr.c \
    libxcorr/xcorr.c

HEADERS += \
    signalprocdispatcher.h \
    basicdefinitions.h \
    networkdriver.h \
    signalprocworker.h \
    abstractcalc.h \
    xcorrcalc.h \
    oscidriver.h \
    vxi11/vxi11_user.h \
    libxcorr/xcorr.h
