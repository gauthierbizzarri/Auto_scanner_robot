#include "camerascanmqttpayload.h"

CameraScanMqttPayload::CameraScanMqttPayload(QString robotId)
{
    data.insert("robot", robotId);
}
