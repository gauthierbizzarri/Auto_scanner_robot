#include "mqttmessageeventmanager.h"

#include <QJsonDocument>


MqttMessageEventManager::MqttMessageEventManager(MQTTManager *manager) : EventManager()
{
    this->manager=manager;

    manager->subscribe(MqttTopic::allUiOrder(), this);
    manager->subscribe(MqttTopic::allRobotButton(), this);
    manager->subscribe(MqttTopic::allCameraColor(), this);
    manager->subscribe(MqttTopic::allRobotStatus(), this);
    manager->subscribe(MqttTopic::allLoadingAreaColor(), this);
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
                    connect(this, SIGNAL(handleCalled(QJsonObject, bool, QMap<QString, QVariant>)), listeners.value(topic), SLOT(handle(QJsonObject, bool, QMap<QString, QVariant>)));
                    emit handleCalled(data.object(), data.isEmpty(), meta);
                    disconnect(this, SIGNAL(handleCalled(QJsonObject, bool, QMap<QString, QVariant>)), listeners.value(topic), SLOT(handle(QJsonObject, bool, QMap<QString, QVariant>)));
                }
            }
        }
    }
}

void MqttMessageEventManager::recieveMessage(QMqttMessage message)
{
    QJsonParseError* error= nullptr;
    QJsonDocument::fromJson(message.payload(), error);
    if(error == nullptr)
    {
        messageQueue.append(message);
    }
}
