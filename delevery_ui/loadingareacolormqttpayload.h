#ifndef LOADINGAREACOLORMQTTPAYLOAD_H
#define LOADINGAREACOLORMQTTPAYLOAD_H

#include "mqttpayload.h"



class LoadingAreaColorMqttPayload : public MqttPayload
{
public:
    LoadingAreaColorMqttPayload(QString color);
};

#endif // LOADINGAREACOLORMQTTPAYLOAD_H
