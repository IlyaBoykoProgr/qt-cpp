TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
QT+= core widgets

SOURCES += \
        graphics.cpp \
        main.cpp

HEADERS += \
    graphics.h \
    tile_types.h \
    weapons.h

RESOURCES += \
    res.qrc
