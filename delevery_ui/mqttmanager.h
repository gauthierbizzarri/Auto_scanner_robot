#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include "mqttpayload.h"
#include "timeoutmanager.h"

#include <QApplication>
#include <QMqttClient>


/**
 * @brief The MqttTopic class
 * Managing the topics you can write and read on to
 */
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

    /**
     * @brief parse
     * Parses a topic from a template to extract meta data from it
     * @param topic
     * @param topicTemplate
     * @param ok set to false if somthing went wrong
     * @return a meta data map, or an empty one
     */
    static QMap<QString, QVariant> parse(QString topic, QString topicTemplate, bool *ok = nullptr)
    {
        QMap<QString, QVariant> res;
        QRegularExpression exp("({.+})");
        if(topic.split("/").count() != topicTemplate.split("/").count())//if topic has different level number in comparison to template
        {
            if(ok != nullptr)
            {
                *ok = false;
            }
            return QMap<QString, QVariant>();
        }
        int levelId = 0;
        Q_FOREACH(QString topicLevel, topic.split("/"))//for each topic level
        {
            QString templateLevel = topicTemplate.split("/").at(levelId);
            if(exp.match(templateLevel).hasMatch())
            {
                res.insert(templateLevel.replace("{", "").replace("}", ""), topicLevel);//extract meta data
            }
            else if(topicLevel != templateLevel)//if a level is different on topic and template
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
    const static QString robotButtonTemplate;
    const static QString cameraColorTemplate;
    const static QString robotPathTemplate;
    const static QString robotStepTemplate;
    const static QString cameraScanTemplate;
    const static QString loadingAreaColorTemplate;

    static MqttTopic allRobotButton()
    {
        QRegularExpression exp("({.+})");
        QString temp=robotButtonTemplate;
        return MqttTopic(temp.replace(exp, "+"), 2);
    }
    static MqttTopic allRobotStatus()
    {
        QRegularExpression exp("({.+})");
        QString temp=robotStepTemplate;
        return MqttTopic(temp.replace(exp, "+"), 1);
    }

    static MqttTopic allLoadingAreaColor()
    {
        QRegularExpression exp("({.+})");
        QString temp=loadingAreaColorTemplate;
        return MqttTopic(temp.replace(exp, "+"), 0);
    }

    static MqttTopic robotPath(QString robotId)
    {
        QRegularExpression exp("({robotid})");
        QString temp=robotPathTemplate;
        return MqttTopic(temp.replace(exp, robotId), 2);
    }

    static MqttTopic loadingAreaColor(int loadingarea)
    {
        QRegularExpression exp("({loadingareaid})");
        QString temp=loadingAreaColorTemplate;
        return MqttTopic(temp.replace(exp, QString::number(loadingarea)), 0);
    }

    static MqttTopic allCameraColor()
    {
        QRegularExpression exp("({.+})");
        QString temp=cameraColorTemplate;
        return MqttTopic(temp.replace(exp, "+"), 2);
    }

    static MqttTopic allUiOrder(){
        QRegularExpression exp("({.+})");
        QString temp=uiOrderTemplate;
        return MqttTopic(temp.replace(exp, "+"), 2);
    };
    static MqttTopic uiOrder(int uiId){
        QRegularExpression exp("({id})");
        QString temp=uiOrderTemplate;
        return MqttTopic(temp.replace(exp, QString::number(uiId)), 2);
    };
    static MqttTopic cameraScan(int camid){
        QRegularExpression exp("({camid})");
        QString temp=cameraScanTemplate;
        return MqttTopic(temp.replace(exp, QString::number(camid)), 2);
    };
};

/**
 * @brief The MQTTManager class
 * Class managing mqtt communication with brocker
 */
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

    /**
     * @brief configureFromConfigString*
     * set configuration from an mqtt configuration string
     * @see AppConfig
     * @param configString
     */
    void configureFromConfigString(QString configString);

    /**
     * @brief connectToHost
     * Connect manager to brocker usint given configuration
     */
    void connectToHost();

    /**
     * @brief subscribe
     * Subscribe to the topic topic, setting the message handler handleObject
     * @param topic
     * @param handleObject
     */
    void subscribe(MqttTopic topic, QObject* handleObject);

    /**
     * @brief publish
     * Publish the payload to the topic on the broclker
     * @param topic
     * @param payload
     */
    void publish(MqttTopic topic, MqttPayload* payload);
private slots:
    void clientConnected();
    void clientTimedout();
signals:
    void connected();
    void timedout();
};

#endif // MQTTMANAGER_H
