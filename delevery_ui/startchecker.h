#ifndef STARTCHECKER_H
#define STARTCHECKER_H

#include "DataChecker.h"



class StartChecker : public DataChecker
{
public:
    StartChecker(int start);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // STARTCHECKER_H
