#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T19:45:09
#
#-------------------------------------------------

QT       += testlib core

QT       += gui

TARGET = tst_qxutiltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += tst_qxutiltest.h

SOURCES += \
    tst_qxutiltest.cpp
SOURCES += ../../../src/lib/qxutil.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

