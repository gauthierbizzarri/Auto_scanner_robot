#include "startchecker.h"

#include <startZones.h>

StartChecker::StartChecker(int start) : DataChecker(start)
{

}

bool StartChecker::check()
{
    if(!startZones.contains(data.toInt()))
    {
        lastError += "La zone de dépot doit être parmis : ";
        Q_FOREACH(int c, startZones)
        {
            lastError += QString::number(c)+", ";
        }
        return false;
    }
    return true;
}

QString StartChecker::checks()
{
    return "Zone de dépot";
}
