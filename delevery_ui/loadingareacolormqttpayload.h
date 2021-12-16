#ifndef LOADINGAREACOLORMQTTPAYLOAD_H
#define LOADINGAREACOLORMQTTPAYLOAD_H

#include "mqttpayload.h"


/**
 * @brief The LoadingAreaColorMqttPayload class
 * Payload for color discoveries to share
 */
class LoadingAreaColorMqttPayload : public MqttPayload
{
public:
    LoadingAreaColorMqttPayload(QString color);
};

#endif // LOADINGAREACOLORMQTTPAYLOAD_H
