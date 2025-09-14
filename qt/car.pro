#-------------------------------------------------
#
# Project created by QtCreator 2021-07-16T17:13:44
#
#-------------------------------------------------
CONFIG += C++11
QT       += core gui network
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car
TEMPLATE = app


SOURCES += main.cpp\
    daochewindow.cpp \
    form_daoche.cpp \
        mainwindow.cpp \
    weather.cpp \
    map.cpp \
    music.cpp \
    video.cpp

HEADERS  += mainwindow.h \
    daochewindow.h \
    distanceworker.h \
    form_daoche.h \
    weather.h \
    map.h \
    music.h \
    video.h \
    weatherdata.h

FORMS    += mainwindow.ui \
    daochewindow.ui \
    form_daoche.ui \
    map.ui \
    music.ui \
    video.ui \
    weather.ui

RESOURCES += \
    img.qrc
