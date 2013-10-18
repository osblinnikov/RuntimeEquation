#-------------------------------------------------
#
# Project created by QtCreator 2010-11-11T20:22:57
#
#-------------------------------------------------
QT       += core
QT       -= gui

TARGET = RunTimeEquation
TEMPLATE = lib
CONFIG += shared
VERSION = 3.0.0

DEFINES += RUNTIMEEQUATION_LIBRARY

SOURCES += runtimeequation.cpp

HEADERS +=RunTimeEquation_global.h \
    ../LoadPlugins/interfaces.h \
    runtimeequation.h
DESTDIR = ../releases/LoadPlugins/plugins
