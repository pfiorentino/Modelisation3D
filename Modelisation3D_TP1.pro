TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    triangle.cpp \
    vertice.cpp \
    surface3d.cpp

HEADERS += \
    triangle.h \
    vertice.h \
    surface3d.h
