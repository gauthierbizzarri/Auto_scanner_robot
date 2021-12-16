#ifndef CAMERASCANMQTTPAYLOAD_H
#define CAMERASCANMQTTPAYLOAD_H

#include "mqttpayload.h"



class CameraScanMqttPayload : public MqttPayload
{
public:
    CameraScanMqttPayload(QString robotId);
};

#endif // CAMERASCANMQTTPAYLOAD_H
