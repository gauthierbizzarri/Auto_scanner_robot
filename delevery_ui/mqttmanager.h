#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include "mqttpayload.h"
#include "timeoutmanager.h"

#include <QApplication>
#include <QMqttClient>


class MqttTopic {
private:
    MqttTopic(QString t, int qos = 0, bool retained = false)
    {
        topic = t;
        this->qos = qos;
        this->retained=retained;
    };
public:
    QString topic;
    bool retained;
    int qos;

    static MqttTopic allUiOrder;
    static MqttTopic uiOrder(int uiId){
        return MqttTopic("field/ui/"+QString::number(uiId)+"/ordre", 2);
    };
};


class MQTTManager : public QObject
{
    Q_OBJECT
private:
    QMqttClient* client;
    bool m_connected;
    TimeoutManager* timeout;
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

    void connectToHost();

    void subscribe(MqttTopic topic, QObject* handleObject);

    void publish(MqttTopic topic, MqttPayload* payload);
private slots:
    void clientConnected();
    void clientTimedout();
signals:
    void connected();
    void timedout();
};

#endif // MQTTMANAGER_H
