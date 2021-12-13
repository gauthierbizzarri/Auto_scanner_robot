#include "uiordermqttpayload.h"

UiOrderMqttPayload::UiOrderMqttPayload(QString color, int loadingArea, int depositArea, QString robotid)
{
    addValue("color", color);
    addValue("loadingArea", loadingArea);
    addValue("depositArea", depositArea);
    addValue("robotId", robotid);
}
