#include "colorchecker.h"

#include <colors.h>

ColorChecker::ColorChecker(QString color) : DataChecker(color)
{

}

bool ColorChecker::check()
{
    bool found = false;
    Q_FOREACH(QString c, colors.keys())
    {
        if(c == data.toString())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        lastError = "La couleur doit être parmis : ";
        Q_FOREACH(QString c, colors.keys())
        {
            lastError += c+", ";
        }
        return false;
    }
    return true;
}

QString ColorChecker::checks()
{
    return "couleur";
}
