#ifndef ROBOTCHECKER_H
#define ROBOTCHECKER_H

#include "DataChecker.h"

#include <QString>



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
