#ifndef MQTTPAYLOAD_H
#define MQTTPAYLOAD_H

#include <QJsonObject>

class MqttPayload
{
protected:
    QJsonObject data;
public:
    MqttPayload();
    virtual QByteArray toJson();
};

#endif // MQTTPAYLOAD_H
