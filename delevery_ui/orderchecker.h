#ifndef ORDERCHECKER_H
#define ORDERCHECKER_H

#include "DataChecker.h"

class OrderChecker : public DataChecker
{
private:
    QList<DataChecker*> checkers;
public:
    OrderChecker(QString color, QString robot, int loadingZone);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // ORDERCHECKER_H
