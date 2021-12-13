#include "loadingzonechecker.h"
#include "LoadingZones.h"

LoadingZoneChecker::LoadingZoneChecker(int loadingZone) : DataChecker(loadingZone)
{

}

bool LoadingZoneChecker::check()
{
    bool found = false;
    Q_FOREACH(int c, loadingZones)
    {
        if(c == data.toInt())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        lastError = "La couleur doit être parmis : ";
        Q_FOREACH(int c, loadingZones)
        {
            lastError += QString::number(c)+", ";
        }
        return false;
    }
    return true;
}

QString LoadingZoneChecker::checks()
{
    return "zone de largage";
}
