#ifndef UIORDERMQTTPAYLOAD_H
#define UIORDERMQTTPAYLOAD_H

#include "mqttpayload.h"



class UiOrderMqttPayload : public MqttPayload
{
public:
    UiOrderMqttPayload(QString color, int loadingArea, int depositArea, QString robotid);
};

#endif // UIORDERMQTTPAYLOAD_H
