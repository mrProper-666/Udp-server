#-------------------------------------------------
#
# Project created by QtCreator 2012-11-01T22:18:59
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    udpserver.cpp

HEADERS += \
    udpserver.h
