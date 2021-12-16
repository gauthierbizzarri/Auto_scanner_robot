#ifndef LOADINGZONECHECKER_H
#define LOADINGZONECHECKER_H

#include "DataChecker.h"


/**
 * @brief The LoadingZoneChecker class
 * Class used to check if a loading area is correct
 */
class LoadingZoneChecker : public DataChecker
{
public:
    LoadingZoneChecker(int loadingZone);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // LOADINGZONECHECKER_H
