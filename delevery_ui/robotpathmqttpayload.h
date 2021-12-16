#ifndef ROBOTPATHMQTTPAYLOAD_H
#define ROBOTPATHMQTTPAYLOAD_H

#include "mqttpayload.h"



class RobotPathMqttPayload : public MqttPayload
{
public:
    RobotPathMqttPayload(QJsonObject data);
};

#endif // ROBOTPATHMQTTPAYLOAD_H
