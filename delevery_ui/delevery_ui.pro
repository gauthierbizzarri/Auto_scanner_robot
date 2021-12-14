QT       += core gui mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appconfig.cpp \
    colorchecker.cpp \
    config.cpp \
    downleftfieldelement.cpp \
    downrightfieldelement.cpp \
    eventmanager.cpp \
    fielddraw.cpp \
    fieldelement.cpp \
    fieldmodel.cpp \
    loadingzonechecker.cpp \
    main.cpp \
    mainwindow.cpp \
    mqttmanager.cpp \
    mqttmessageeventmanager.cpp \
    mqttpayload.cpp \
    orderchecker.cpp \
    robotchecker.cpp \
    startchecker.cpp \
    tdownfieldelement.cpp \
    timeoutmanager.cpp \
    tleftfieldelement.cpp \
    trightfieldelement.cpp \
    tupfieldelement.cpp \
    turndownrightfieldelement.cpp \
    uiorderhandler.cpp \
    uiordermqttpayload.cpp \
    upleftfieldelement.cpp \
    uprightfieldelement.cpp

HEADERS += \
    DataChecker.h \
    LoadingZones.h \
    StartZones.h \
    appconfig.h \
    colorchecker.h \
    colors.h \
    config.h \
    direction.h \
    downleftfieldelement.h \
    downrightfieldelement.h \
    eventlistener.h \
    eventmanager.h \
    fielddraw.h \
    fieldelement.h \
    fieldmodel.h \
    loadingzonechecker.h \
    mainwindow.h \
    mqttmanager.h \
    mqttmessageeventmanager.h \
    mqttpayload.h \
    orderchecker.h \
    robotchecker.h \
    startchecker.h \
    tdownfieldelement.h \
    timeoutmanager.h \
    tleftfieldelement.h \
    trightfieldelement.h \
    tupfieldelement.h \
    turndownrightfieldelement.h \
    uiorderhandler.h \
    uiordermodel.h \
    uiordermqttpayload.h \
    upleftfieldelement.h \
    uprightfieldelement.h

FORMS += \
    config.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
