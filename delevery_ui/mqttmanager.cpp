#include "mqttmanager.h"

#include <QApplication>

MqttTopic MqttTopic::allUiOrder("field/ui/#/ordre", 2);

QString MQTTManager::defaultProtocol = "mqtt5.0";

MQTTManager::MQTTManager(QApplication *app)
{
    client = new QMqttClient(app);
}

MQTTManager *MQTTManager::configurePort(int port)
{
    client->setPort(port);
    return this;
}

MQTTManager *MQTTManager::configureHost(QString host)
{
    client->setHostname(host);
    return this;
}

MQTTManager *MQTTManager::configureUsername(QString username)
{
    client->setUsername(username);
    return this;
}

MQTTManager *MQTTManager::configurePassword(QString password)
{
    client->setPassword(password);
    return this;
}

MQTTManager *MQTTManager::configureClientId(QString clientId)
{
    client->setClientId(clientId);
    return this;
}

MQTTManager *MQTTManager::configureProtocolVersion(QString protocolVersion)
{
    if(admitedProtocols.contains(protocolVersion))
    {
        client->setProtocolVersion(admitedProtocols.value(protocolVersion));
        return this;
    }
    client->setProtocolVersion(admitedProtocols.value(defaultProtocol));
    return this;
}

MQTTManager *MQTTManager::configureKeepAlive(int keepalive)
{
    client->setKeepAlive(keepalive);
    return this;
}

void MQTTManager::configureFromConfigString(QString configString)
{
    Q_FOREACH(QString option, configString.split(";"))
    {
        if(option.split(":").count() == 2)
        {
            QString optionName = option.split(":")[0];
            QString optionValue = option.split(":")[1];
            if(!optionValue.isEmpty() && !optionName.isEmpty())
            {
                if(optionName == "port")
                {
                    bool ok = false;
                    int port = optionName.toInt(&ok);
                    if(ok)
                    {
                        configurePort(port);
                    }
                }
                else if(optionName == "host")
                {
                    configureHost(optionValue);
                }
                else if(optionName == "username")
                {
                    configureUsername(optionValue);
                }
                else if(optionName == "password")
                {
                    configurePassword(optionValue);
                }
                else if(optionName == "clientid")
                {
                    configureClientId(optionValue);
                }
                else if(optionName == "protocolversion")
                {
                    configureProtocolVersion(optionValue);
                }
                else if(optionName == "keepalive")
                {
                    bool ok = false;
                    int keepalive = optionName.toInt(&ok);
                    if(ok)
                    {
                        configureKeepAlive(keepalive);
                    }
                }
            }
        }
    }
}

void MQTTManager::connectToHost()
{
    client->connectToHost();
}

void MQTTManager::subscribe(MqttTopic topic, QObject *handleObject)
{
    QMqttSubscription* sub = client->subscribe(topic.topic);
    connect(sub, SIGNAL(messageReceived(QMqttMessage)), handleObject, SLOT(recieveMessage(QMqttMessage)));
}

void MQTTManager::publish(MqttTopic topic, MqttPayload *payload)
{
    client->publish(topic.topic, payload->toJson(), topic.qos, topic.retained);
}
