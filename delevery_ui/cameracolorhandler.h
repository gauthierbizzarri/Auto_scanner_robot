#ifndef CAMERACOLORHANDLER_H
#define CAMERACOLORHANDLER_H

#include "eventlistener.h"
#include "fieldmodel.h"
#include "iconlabel.h"



class CameraColorHandler : public EventListener
{
private:
    IconLabel* packet;
    FieldModel* model;
public:
    CameraColorHandler(IconLabel* packet, FieldModel* model);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // CAMERACOLORHANDLER_H
