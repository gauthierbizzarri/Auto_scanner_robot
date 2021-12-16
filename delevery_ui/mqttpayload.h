#ifndef MQTTPAYLOAD_H
#define MQTTPAYLOAD_H

#include <QJsonObject>

/**
 * @brief The MqttPayload class
 * Base class for mqtt payload (just a layer above a simple json)
 */
class MqttPayload
{
protected:
    QJsonObject data;
public:
    MqttPayload();
    virtual QByteArray toJson();
};

#endif // MQTTPAYLOAD_H
