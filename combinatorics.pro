TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS += -std=gnu++1z
QMAKE_CXXFLAGS += -std=c++1z

SOURCES += main.cpp

HEADERS += \
    ../../Dropbox/src/utils/math_grostig.h
