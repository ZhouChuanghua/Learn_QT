#-------------------------------------------------
#
# Project created by QtCreator 2017-09-17T20:19:17
#
#-------------------------------------------------

QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


LIBS += -LC:/Users/zhwsd/Desktop/work/Learn_QT/FirstProject_Test/project/ -lControlCAN
# LIBS += -LC:\Users\zhwsd\Desktop\work\Learn_QT\FirstProject_Test\project -lControlCAN

# LIBS += ControlCAN.LIB

# CONFIG += console

# win32:QMAKE_LFLAGS += -shared
# CONFIG += shared


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        callout.cpp \
        chart.cpp \
        chartview.cpp \
        main.cpp \
        mainwindow.cpp \
        qwchartview.cpp

HEADERS += \
    callout.h \
    chart.h \
    chartview.h \
        mainwindow.h \
    ControlCAN.h \
    qwchartview.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    ControlCAN.LIB
