#ifndef STARTCHECKER_H
#define STARTCHECKER_H

#include "DataChecker.h"


/**
 * @brief The StartChecker class
 * Check if a deposit start zone is valid
 */
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
