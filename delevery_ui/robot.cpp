#include "robot.h"

Robot::Robot()
{
    this->pos = QPoint(0, 0);
    this->color = QColor(0, 0, 0);
    status = RobotStatus::TOLOAD;
    dir = UP;
    readyForOrder = false;
    carryingColor = "";
    start=pos;
}

Robot::Robot(QPoint ipos, QColor color, Direction dir= UP)
{
    this->pos=ipos;
    this->color=color;
    status = RobotStatus::TOLOAD;
    this->dir = dir;
    readyForOrder = false;
    carryingColor = "";
    start = ipos;
}

void Robot::moveAt(QPoint p)
{
    pos = p;
}

QPoint Robot::startedOn()
{
    return start;
}

QColor Robot::getColor()
{
    return color;
}

QPoint Robot::getPosition()
{
    return pos;
}

Direction Robot::pointing()
{
    return dir;
}

void Robot::setDirection(Direction d)
{
    dir = d;
}

void Robot::setReadyForOrder(bool ready)
{
    readyForOrder = ready;
}

RobotStatus Robot::getStatus()
{
    return status;
}

void Robot::setStatus(RobotStatus s)
{
    status=s;
}

bool Robot::isReadyForOrder()
{
    return readyForOrder;
}

void Robot::setCarryingColor(QString color)
{
    carryingColor = color;
}

QString Robot::getCarriedColor()
{
    return carryingColor;
}

void Robot::setColorToLookFor(QString color)
{
    lookingForColor = color;
}

QString Robot::getColorToLookFor()
{
    return lookingForColor;
}
