QT       += core gui mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appconfig.cpp \
    colorchecker.cpp \
    loadingzonechecker.cpp \
    main.cpp \
    mainwindow.cpp \
    mqttmanager.cpp \
    orderchecker.cpp \
    robotchecker.cpp \
    startchecker.cpp

HEADERS += \
    DataChecker.h \
    LoadingZones.h \
    StartZones.h \
    appconfig.h \
    colorchecker.h \
    colors.h \
    loadingzonechecker.h \
    mainwindow.h \
    mqttmanager.h \
    orderchecker.h \
    robotchecker.h \
    startchecker.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
