QT += core
QT -= gui
CONFIG += console c++11
TARGET = interpolation
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

SOURCES += main.cpp \
    polynomial.cpp \
    linear_equation.cpp \
    integrate.cpp

HEADERS += \
    polynomial.h \
    linear_equation.h \
    integrate.h

