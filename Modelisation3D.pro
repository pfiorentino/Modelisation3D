TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    triangle.cpp \
    surface3d.cpp \
    point3d.cpp \
    node.cpp \
    grid3d.cpp \
    hexahedra.cpp \
    sphere.cpp \
    implicitobject.cpp \
    doublesphere.cpp \
    nsphere.cpp \
    points.cpp \
    layout.cpp

HEADERS += \
    triangle.h \
    surface3d.h \
    point3d.h \
    node.h \
    grid3d.h \
    hexahedra.h \
    sphere.h \
    implicitobject.h \
    doublesphere.h \
    nsphere.h \
    points.h \
    layout.h
