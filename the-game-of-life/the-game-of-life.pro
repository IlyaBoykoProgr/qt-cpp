QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = the-game-of-life
TEMPLATE = app


SOURCES += main.cpp\
        universal.cpp

HEADERS  += universal.h

QMAKE_LFLAGS+= -static -static-libstdc++ -static-libgcc
