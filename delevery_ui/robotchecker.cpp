#include "robotchecker.h"

RobotChecker::RobotChecker(QString robot) : DataChecker(robot)
{

}

bool RobotChecker::check()
{
    if(data.toString().isEmpty())
    {
        lastError = "Le champ robot doit être défini";
        return false;
    }
    return true;
}

QString RobotChecker::checks()
{
    return "robot";
}
