#ifndef COLORCHECKER_H
#define COLORCHECKER_H

#include "DataChecker.h"



class ColorChecker: public DataChecker
{
public:
    ColorChecker(QString color);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // COLORCHECKER_H
