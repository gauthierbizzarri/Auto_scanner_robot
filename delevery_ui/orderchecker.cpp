#include "orderchecker.h"
#include "colorchecker.h"
#include "robotchecker.h"
#include "loadingzonechecker.h"

#include <QComboBox>

OrderChecker::OrderChecker(QString color, QList<QString> colors, QString robot, int loadingZone) : DataChecker("")
{
    checkers.append(new ColorChecker(color, colors));
    checkers.append(new RobotChecker(robot));
    checkers.append(new LoadingZoneChecker(loadingZone));
}

bool OrderChecker::check()
{
    Q_FOREACH(DataChecker* checker, checkers)//check if each and every checker passes the test
    {
        if(!checker->check())
        {
            emit refute(checker->checks(), checker->getLastError());
            return false;
        }
    }
    emit validate();
    return true;
}

QString OrderChecker::checks()
{
    return "ordre";
}
