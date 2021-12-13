#include "mqttpayload.h"

#include <QJsonDocument>

MqttPayload::MqttPayload()
{

}

void MqttPayload::addValue(QString field, QVariant data)
{
    this->data.insert(field, data.toString());
}

QByteArray MqttPayload::toJson()
{
    return QJsonDocument(data).toJson();
}
