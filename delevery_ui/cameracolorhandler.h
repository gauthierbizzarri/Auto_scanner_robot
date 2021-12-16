#ifndef CAMERACOLORHANDLER_H
#define CAMERACOLORHANDLER_H

#include "eventlistener.h"
#include "fieldmodel.h"
#include "iconlabel.h"
#include "mqttmanager.h"



class CameraColorHandler : public EventListener
{
private:
    IconLabel* packet;
    FieldModel* model;
     MQTTManager* manager;
public:
    CameraColorHandler(IconLabel* packet, MQTTManager* manager, FieldModel* model);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // CAMERACOLORHANDLER_H
