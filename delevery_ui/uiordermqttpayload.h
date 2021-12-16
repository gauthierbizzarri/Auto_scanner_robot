#ifndef UIORDERMQTTPAYLOAD_H
#define UIORDERMQTTPAYLOAD_H

#include "mqttpayload.h"


/**
 * @brief The UiOrderMqttPayload class
 * Payload class used to send order histories
 */
class UiOrderMqttPayload : public MqttPayload
{
public:
    UiOrderMqttPayload(QString color, int loadingArea, int depositArea, QString robotid);
};

#endif // UIORDERMQTTPAYLOAD_H
