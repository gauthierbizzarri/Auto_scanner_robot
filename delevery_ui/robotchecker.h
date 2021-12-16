#ifndef ROBOTCHECKER_H
#define ROBOTCHECKER_H

#include "DataChecker.h"

#include <QString>


/**
 * @brief The RobotChecker class
 * Check if the selected robot is correct
 */
class RobotChecker : public DataChecker
{
public:
    RobotChecker(QString robot);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // ROBOTCHECKER_H
