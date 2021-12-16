#ifndef CAMERASCANMQTTPAYLOAD_H
#define CAMERASCANMQTTPAYLOAD_H

#include "mqttpayload.h"


/**
 * @brief The CameraScanMqttPayload class
 * Class representing the payload for launching the camera scan
 */
class CameraScanMqttPayload : public MqttPayload
{
public:
    CameraScanMqttPayload(QString robotId);
};

#endif // CAMERASCANMQTTPAYLOAD_H
