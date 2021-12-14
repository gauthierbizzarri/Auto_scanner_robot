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

    static QMap<QString, QVariant> parse(QString topic, QString topicTemplate, bool *ok = nullptr)
    {
        QMap<QString, QVariant> res;
        QRegularExpression exp("({.+})");
        if(topic.split("/").count() != topicTemplate.split("/").count())
        {
            if(ok != nullptr)
            {
                *ok = false;
            }
            return QMap<QString, QVariant>();
        }
        int levelId = 0;
        Q_FOREACH(QString topicLevel, topic.split("/"))
        {
            QString templateLevel = topicTemplate.split("/").at(levelId);
            if(exp.match(templateLevel).hasMatch())
            {
                res.insert(templateLevel.replace("{", "").replace("}", ""), topicLevel);
            }
            else if(topicLevel != templateLevel)
            {
                if(ok != nullptr)
                {
                    *ok = false;
                }
                return QMap<QString, QVariant>();
            }
            levelId ++;
        }
        if(ok != nullptr)
        {
            *ok = true;
        }
        return res;
    }

    const static QString uiOrderTemplate;

    static MqttTopic allUiOrder(){
        QRegularExpression exp("({.+})");
        QString temp=uiOrderTemplate;
        return MqttTopic(temp.replace(exp, "+"), 2);
    };
    static MqttTopic uiOrder(int uiId){
        QRegularExpression exp("({.+})");
        QString temp=uiOrderTemplate;
        return MqttTopic(temp.replace(exp, QString::number(uiId)), 2);
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
    static const QMap<QString, QMqttClient::ProtocolVersion> admitedProtocols;

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
