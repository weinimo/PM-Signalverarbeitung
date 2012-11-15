#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T20:07:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Signalverarbeitung
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

SOURCES += main.cpp \
    signalprocdispatcher.cpp \
    networkdriver.cpp \
    signalprocworker.cpp \
    abstractcalc.cpp \
    xcorrcalc.cpp \
    oscidriver.cpp

HEADERS += \
    signalprocdispatcher.h \
    basicdefinitions.h \
    networkdriver.h \
    signalprocworker.h \
    abstractcalc.h \
    xcorrcalc.h \
    oscidriver.h
