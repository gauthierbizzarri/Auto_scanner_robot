#ifndef MQTTPAYLOAD_H
#define MQTTPAYLOAD_H

#include <QJsonObject>

class MqttPayload
{
protected:
    QJsonObject data;
public:
    MqttPayload();
    void addValue(QString field, QVariant data);
    QByteArray toJson();
};

#endif // MQTTPAYLOAD_H
