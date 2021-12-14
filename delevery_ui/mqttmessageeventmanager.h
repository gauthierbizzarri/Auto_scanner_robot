#ifndef MQTTMESSAGEEVENTMANAGER_H
#define MQTTMESSAGEEVENTMANAGER_H

#include "eventmanager.h"

#include <mqttmanager.h>
#include <QQueue>
#include <QMqttMessage>


class MqttMessageEventManager : public EventManager
{
    Q_OBJECT
private:
    MQTTManager* manager;
    QQueue<QMqttMessage> messageQueue;
public:
    MqttMessageEventManager(MQTTManager* manager);

    // EventManager interface
public slots:
    void process();
    void recieveMessage(QMqttMessage);
};

#endif // MQTTMESSAGEEVENTMANAGER_H
