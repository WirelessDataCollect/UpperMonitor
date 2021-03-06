#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T15:20:07
#
#-------------------------------------------------


QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WiFiGui
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    calibration.cpp \
    fit.cpp \
        myudp.cpp \
    chartswidgt.cpp \
    mytcpclient.cpp \
    chartview.cpp \
    login.cpp \
    md5.cpp \
    setting.cpp \
    device.cpp \
    devicesignal.cpp \
    devicesystem.cpp \
    mainwin.cpp \
    dialogconf.cpp \
    doubleslider.cpp \
    qwcomboboxdelegate.cpp \
    devicecan.cpp \
    signaldata.cpp \
    datadialog.cpp

HEADERS  += \
    calibration.h \
    fit.h \
    myudp.h \
    chartswidgt.h \
    mytcpclient.h \
    chartview.h \
    myeventfilter.h \
    login.h \
    md5.h \
    setting.h \
    device.h \
    devicesignal.h \
    devicesystem.h \
    mainwin.h \
    dialogconf.h \
    doubleslider.h \
    mytcpclient.h \
    qwcomboboxdelegate.h \
    devicecan.h \
    exprtk.hpp \
    signaldata.h \
    datadialog.h

FORMS    += login.ui \
    calibration.ui \
    setting.ui \
    mainwin.ui \
    dialogconf.ui \
    datadialog.ui

RESOURCES += \
    src.qrc

DISTFILES += \
    readme.md
RC_ICONS = ./ico/logo.ico
## exprtk.hpp 段过多
win32:QMAKE_CXXFLAGS +=/bigobj

## MinGW64
#QMAKE_CXXFLAGS +=-Wa,-mbig-obj

##禁止打印信息
DEFINES += QT_NO_DEBUG_OUTPUT
