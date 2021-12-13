#ifndef LOADINGZONECHECKER_H
#define LOADINGZONECHECKER_H

#include "DataChecker.h"



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
