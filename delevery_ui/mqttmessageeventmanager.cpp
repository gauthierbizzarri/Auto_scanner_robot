#include "mqttmessageeventmanager.h"

#include <QJsonDocument>


MqttMessageEventManager::MqttMessageEventManager(MQTTManager *manager) : EventManager()
{
    this->manager=manager;

    manager->subscribe(MqttTopic::allUiOrder(), this);
    manager->subscribe(MqttTopic::allRobotButton(), this);
    manager->subscribe(MqttTopic::allCameraColor(), this);
    manager->subscribe(MqttTopic::allRobotStatus(), this);
}

void MqttMessageEventManager::process()
{
    while(!closed)
    {
        if(!messageQueue.isEmpty())
        {
            QMqttMessage message = messageQueue.takeFirst();
            Q_FOREACH(QString topic, listeners.keys())
            {
                bool accurate = true;
                QMap<QString, QVariant> meta = MqttTopic::parse(message.topic().name(), topic, &accurate);
                if(accurate)
                {
                    QJsonDocument data = QJsonDocument::fromJson(message.payload());
                    listeners.value(topic)->handle(data.object(), data.isEmpty(), meta);
                }
            }
        }
    }
}

void MqttMessageEventManager::recieveMessage(QMqttMessage message)
{
    messageQueue.append(message);
}
