#-------------------------------------------------
#
# Project created by QtCreator 2016-09-01T18:05:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalendarStats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    icscalendar.cpp

HEADERS  += mainwindow.h \
    icscalendar.h

FORMS    += mainwindow.ui

LIBS += -lical

DISTFILES += \
    CmakeLists.txt
