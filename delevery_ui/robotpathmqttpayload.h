#ifndef ROBOTPATHMQTTPAYLOAD_H
#define ROBOTPATHMQTTPAYLOAD_H

#include "mqttpayload.h"


/**
 * @brief The RobotPathMqttPayload class
 * Payload to send the path throught mqtt
 */
class RobotPathMqttPayload : public MqttPayload
{
public:
    RobotPathMqttPayload(QJsonObject data);
};

#endif // ROBOTPATHMQTTPAYLOAD_H
