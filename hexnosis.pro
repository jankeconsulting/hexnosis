#------------------------------------------------------
#
# Copyright (c) 2014 Ralph Janke. All rights reserved.
# 
# Author: Ralph Janke nestle@jankeconsulting.ca
#
#------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SUBDIRS += src \
    test/lib/QxUtilTest
TEMPLATE = subdirs
CONFIG(release, debug|release) {
  DEFINES -= DEBUG
}

CONFIG(debug, debug|release) {
  DEFINES += DEBUG
}

CONFIG(debug, debug|release):message(Project is built in DEBUG mode.)
CONFIG(release, debug|release):message(Project is built in RELEASE mode.)

