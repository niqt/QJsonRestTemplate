#-------------------------------------------------
#
# Project created by QtCreator 2014-07-28T14:00:30
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../qjsonresttemplate.cpp \
    Product.cpp

HEADERS += \
    ../../JsonClassInterface.h \
    ../../qjsonresttemplate.h \
    ../../types.h \
    Product.h
