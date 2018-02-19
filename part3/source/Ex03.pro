QT += core
QT -= gui
CONFIG += console c++11
TARGET = Ex03
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

SOURCES += main.cpp \
    matrix.cpp \
    polynomial.cpp

HEADERS += \
    matrix.h \
    dataloader.h \
    statistic.h \
    polynomial.h \
    ode.h

