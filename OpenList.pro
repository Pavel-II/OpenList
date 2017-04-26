#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T15:26:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenList
TEMPLATE = app


SOURCES += main.cpp\
        mw_ol.cpp \
    filedownloader.cpp \
    openvpnclient.cpp \
    dsettings.cpp \
    statuswidget.cpp

HEADERS  += mw_ol.h \
    filedownloader.h \
    openvpnclient.h \
    dsettings.h \
    statuswidget.h

FORMS    += mw_ol.ui \
    dsettings.ui \
    statuswidget.ui
