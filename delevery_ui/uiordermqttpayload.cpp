#include "uiordermqttpayload.h"

UiOrderMqttPayload::UiOrderMqttPayload(QString color, int loadingArea, int depositArea, QString robotid)
{
    data.insert("color", color);
    data.insert("loadingArea", loadingArea);
    data.insert("depositArea", depositArea);
    data.insert("robotId", robotid);
}
