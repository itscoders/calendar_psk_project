#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T13:24:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calendar
TEMPLATE = app


SOURCES += main.cpp\
        calendarwindow.cpp \
    logwindow.cpp \
    inserteventwindow.cpp \
    insertmenueventwindow.cpp \
    sqldatebase.cpp \
    adduser.cpp \
    calculatedayofweek.cpp

HEADERS  += calendarwindow.h \
    logwindow.h \
    inserteventwindow.h \
    insertmenueventwindow.h \
    sqldatebase.h \
    adduser.h \
    calculatedayofweek.h

FORMS    += calendarwindow.ui \
    logwindow.ui \
    inserteventwindow.ui \
    insertmenueventwindow.ui \
    adduser.ui \
    calculatedayofweek.ui
