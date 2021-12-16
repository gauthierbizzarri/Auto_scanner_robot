#include "mqttpayload.h"

#include <QJsonDocument>
#include <QJsonArray>

MqttPayload::MqttPayload()
{

}

QByteArray MqttPayload::toJson()
{
    return QJsonDocument(data).toJson();
}
