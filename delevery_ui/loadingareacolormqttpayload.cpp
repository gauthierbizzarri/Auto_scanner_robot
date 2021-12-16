#include "loadingareacolormqttpayload.h"

LoadingAreaColorMqttPayload::LoadingAreaColorMqttPayload(QString color)
{
    data.insert("color", color);
}
