#ifndef ORDERCHECKER_H
#define ORDERCHECKER_H

#include "DataChecker.h"

/**
 * @brief The OrderChecker class
 * Class used to check if an order is valid, user multiple sub checkers
 */
class OrderChecker : public DataChecker
{
private:
    QList<DataChecker*> checkers;
public:
    OrderChecker(QString color, QList<QString> colors, QString robot, int loadingZone);

    // DataChecker interface
public:
    bool check();
    QString checks();
};

#endif // ORDERCHECKER_H
