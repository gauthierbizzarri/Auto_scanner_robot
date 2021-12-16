#ifndef MQTTMESSAGEEVENTMANAGER_H
#define MQTTMESSAGEEVENTMANAGER_H

#include "eventmanager.h"

#include <mqttmanager.h>
#include <QQueue>
#include <QMqttMessage>

/**
 * @brief The MqttMessageEventManager class
 * Event manager specialised in managing mqtt messages events
 */
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
