#ifndef COLORCHECKER_H
#define COLORCHECKER_H

#include "DataChecker.h"


/**
 * @brief The ColorChecker class
 * Class used to check if a color value is ok
 */
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
