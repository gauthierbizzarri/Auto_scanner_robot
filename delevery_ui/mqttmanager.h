#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QApplication>
#include <QMqttClient>



class MQTTManager
{
private:
    QMqttClient* client;

public:
    static QString defaultProtocol;
    MQTTManager(QApplication *app);

    MQTTManager *configurePort(int port);

    MQTTManager* configureHost(QString host);

    MQTTManager* configureUsername(QString username);

    MQTTManager* configurePassword(QString password);

    MQTTManager* configureClientId(QString clientId);

    MQTTManager* configureProtocolVersion(QString protocolVersion);
    const QMap<QString, QMqttClient::ProtocolVersion> admitedProtocols{
         {"mqtt3.1", QMqttClient::MQTT_3_1},
        {"mqtt3.1.1", QMqttClient::MQTT_3_1_1},
        {"mqtt5.0", QMqttClient::MQTT_5_0}
    };

    MQTTManager* configureKeepAlive(int keepalive);

    void configureFromConfigString(QString configString);
};

QString MQTTManager::defaultProtocol = "mqtt5.0";

#endif // MQTTMANAGER_H
