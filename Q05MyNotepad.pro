#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T11:19:46
#
#-------------------------------------------------

QT       += core gui printsupport multimedia axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Q05MyNotepad
TEMPLATE = app

RC_ICONS = ccat.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    res.qrc
