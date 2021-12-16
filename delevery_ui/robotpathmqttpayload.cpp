#include "robotpathmqttpayload.h"

#include <QJsonArray>

RobotPathMqttPayload::RobotPathMqttPayload(QJsonObject data)
{
    if(!data.contains("data"))
    {
        this->data.insert("data", QJsonArray());
        this->data.insert("size", 0);
    }
    else
    {
        Q_FOREACH(QString key, data.keys())
        {
            this->data.insert(key, data.value(key));
        }
    }
}
