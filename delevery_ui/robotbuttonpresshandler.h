#ifndef ROBOTBUTTONPRESSHANDLER_H
#define ROBOTBUTTONPRESSHANDLER_H

#include "eventlistener.h"
#include "fieldmodel.h"
#include "iconlabel.h"

#include <QCommandLinkButton>
#include <mqttmanager.h>



class RobotButtonPressHandler : public EventListener
{
private:
    IconLabel* order;
    IconLabel* package;
    FieldModel* field;
    IconLabel* color;
    MQTTManager* manager;
public:
    RobotButtonPressHandler(IconLabel* order, IconLabel* package, IconLabel* color, MQTTManager* manager, FieldModel* field);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // ROBOTBUTTONPRESSHANDLER_H
