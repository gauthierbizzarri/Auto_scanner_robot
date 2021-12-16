#include "mqttmanager.h"
#include "mqttmessageeventmanager.h"

#include <QApplication>

//templates definitions
const QString MqttTopic::uiOrderTemplate = "field/ui/{id}/ordre";
const QString MqttTopic::robotButtonTemplate = "field/robot/{robotid}/button";
const QString MqttTopic::cameraColorTemplate = "field/camera/{camid}/color";
const QString MqttTopic::robotPathTemplate = "field/robot/{robotid}/path";
const QString MqttTopic::robotStepTemplate = "field/robot/{robotid}/status";
const QString MqttTopic::cameraScanTemplate = "field/camera/{camid}/scan";
const QString MqttTopic::loadingAreaColorTemplate = "field/loading_area/{loadingareaid}/color";

//default mqtt protocol to use
QString MQTTManager::defaultProtocol = "mqtt3.1.1";

//allowed mqtt protocols to use
const QMap<QString, QMqttClient::ProtocolVersion> MQTTManager::admitedProtocols{
         {"mqtt3.1", QMqttClient::MQTT_3_1},
        {"mqtt3.1.1", QMqttClient::MQTT_3_1_1},
        {"mqtt5.0", QMqttClient::MQTT_5_0}
    };

MQTTManager::MQTTManager(QApplication *app)
{
    client = new QMqttClient(app);
    m_connected = false;
    timeout = new TimeoutManager(30);
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
                    int port = optionValue.toInt(&ok, 10);
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
    connect(client, SIGNAL(stateChanged(ClientState)), this, SLOT(clientConnected()));
    connect(timeout, SIGNAL(timedout()), this, SLOT(clientTimedout()));
    client->connectToHost();
    TimeoutManager::launch(timeout);
}

void MQTTManager::subscribe(MqttTopic topic, QObject *handleObject)
{
    if(m_connected)
    {
        QMqttSubscription* sub = client->subscribe(topic.topic);
        connect(sub, SIGNAL(messageReceived(QMqttMessage)), handleObject, SLOT(recieveMessage(QMqttMessage)), Qt::ConnectionType::DirectConnection);
    }
}

void MQTTManager::publish(MqttTopic topic, MqttPayload *payload)
{
    if(m_connected)
    {
        QByteArray json = payload->toJson();
        int res = client->publish(topic.topic, json, topic.qos, topic.retained);
        qDebug()<<"publish count : "<<res;
    }
}

void MQTTManager::clientConnected()
{
    if(!timeout->timeoutReached && client->state() == QMqttClient::Connected)//if connection did not time out
    {
        timeout->abort();
        m_connected = true;
        emit connected();
    }
}

void MQTTManager::clientTimedout()
{
    emit timedout();//when connection did time out
}
