#include "colorchecker.h"

#include <colors.h>

ColorChecker::ColorChecker(QString color, QList<QString> colors) : DataChecker(color)
{
    this->colors = colors;
}

bool ColorChecker::check()
{
    bool found = false;
    //find the color
    Q_FOREACH(QString c, colors)
    {
        if(c == data.toString())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        //if not found
        lastError = "La couleur doit être parmis : ";
        Q_FOREACH(QString c, colors)
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
