QT       += core gui mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StateColors.cpp \
    appconfig.cpp \
    cameracolorhandler.cpp \
    camerascanmqttpayload.cpp \
    colorchecker.cpp \
    config.cpp \
    downleftfieldelement.cpp \
    downrightfieldelement.cpp \
    eventmanager.cpp \
    fielddraw.cpp \
    fieldelement.cpp \
    fieldmodel.cpp \
    iconlabel.cpp \
    jsonpathmaker.cpp \
    loadingzonechecker.cpp \
    main.cpp \
    mainwindow.cpp \
    mqttmanager.cpp \
    mqttmessageeventmanager.cpp \
    mqttpayload.cpp \
    objectpathmaker.cpp \
    orderchecker.cpp \
    orderfollower.cpp \
    robot.cpp \
    robotbuttonpresshandler.cpp \
    robotchecker.cpp \
    robotpathmqttpayload.cpp \
    robotstephandler.cpp \
    startchecker.cpp \
    straightleftrightfieldelement.cpp \
    straightupdownfieldelement.cpp \
    tdownfieldelement.cpp \
    timeoutmanager.cpp \
    tleftfieldelement.cpp \
    trightfieldelement.cpp \
    tupfieldelement.cpp \
    turndownleftfieldelement.cpp \
    turndownrightfieldelement.cpp \
    turnupleftfieldelement.cpp \
    turnuprightfieldelement.cpp \
    uiorderhandler.cpp \
    uiordermqttpayload.cpp \
    upleftfieldelement.cpp \
    uprightfieldelement.cpp

HEADERS += \
    DataChecker.h \
    FieldElementTracker.h \
    LoadingZones.h \
    StartZones.h \
    StateColors.h \
    appconfig.h \
    cameracolorhandler.h \
    cameraids.h \
    camerascanmqttpayload.h \
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
    iconlabel.h \
    jsonpathmaker.h \
    loadingzonechecker.h \
    mainwindow.h \
    mqttmanager.h \
    mqttmessageeventmanager.h \
    mqttpayload.h \
    objectpathmaker.h \
    orderchecker.h \
    orderfollower.h \
    pathmaker.h \
    robot.h \
    robotbuttonpresshandler.h \
    robotchecker.h \
    robotpathmqttpayload.h \
    robotstephandler.h \
    startchecker.h \
    straightleftrightfieldelement.h \
    straightupdownfieldelement.h \
    tdownfieldelement.h \
    timeoutmanager.h \
    tleftfieldelement.h \
    trightfieldelement.h \
    tupfieldelement.h \
    turndownleftfieldelement.h \
    turndownrightfieldelement.h \
    turnupleftfieldelement.h \
    turnuprightfieldelement.h \
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
