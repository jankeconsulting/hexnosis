#------------------------------------------------------
#
# Copyright (c) 2014 Ralph Janke. All rights reserved.
# 
# Author: Ralph Janke nestle@jankeconsulting.ca
#
#------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hexnosis
TEMPLATE = app

SOURCES += main.cpp\
    hexpanel.cpp \
    hexfilemodel.cpp \
    hexpanelitemdelegate.cpp \
    textpanelitemdelegate.cpp \
    textpanel.cpp \
    tabpanel.cpp \
    hextabwidget.cpp \
    hexnosiswindow.cpp \
    hexfilemodelpanel.cpp \
    lib/qxvalidator.cpp \
    lib/qxutil.cpp \
    aboutdialog.cpp \
    licensedialog.cpp

HEADERS  += \
    hexpanel.h \
    hexfilemodel.h \
    hexpanelitemdelegate.h \
    textpanelitemdelegate.h \
    textpanel.h \
    tabpanel.h \
    hextabwidget.h \
    hexnosiswindow.h \
    hexfilemodelpanel.h \
    lib/qxvalidator.h \
    lib/qxutil.h \
    aboutdialog.h \
    licensedialog.h

FORMS    += \
    hexnosiswindow.ui \
    aboutdialog.ui \
    licensedialog.ui

CONFIG(release, debug|release) {
  DEFINES -= DEBUG
}

CONFIG(debug, debug|release) {
  DEFINES += DEBUG
}

CONFIG(debug, debug|release):message(Project is built in DEBUG mode.)
CONFIG(release, debug|release):message(Project is built in RELEASE mode.)

RESOURCES += \
    hexnosis.qrc

OTHER_FILES +=
