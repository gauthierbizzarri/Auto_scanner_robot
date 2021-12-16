#include "robot.h"

#include <QPainterPath>
#include "fieldelement.h"

Robot::Robot()
{
    this->pos = QPoint(0, 0);
    this->color = QColor(0, 0, 0);
    status = RobotStatus::TOLOAD;
    dir = UP;
    readyForOrder = true;
    carryingColor = "";
    start=pos;
}

Robot::Robot(QPoint ipos, QColor color, Direction dir= UP)
{
    this->pos=ipos;
    this->color=color;
    status = RobotStatus::TOLOAD;
    this->dir = dir;
    readyForOrder = true;
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

void Robot::setStartPoint(QPoint p)
{
    start = p;
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

void Robot::draw(QPainter *p)
{
    int robSize = FieldElement::thickness+10;
    QPainterPath rpath;
    //draw robot body
    rpath.addEllipse(getPosition().x()*FieldElement::size+FieldElement::size/2-robSize/2, getPosition().y()*FieldElement::size+FieldElement::size/2-robSize/2, robSize, robSize);
    p->fillPath(rpath, QBrush(getColor()));
    QPainterPath arrow;
    QPolygonF trig;
    int offset = 2;
    //draw robot "head"
    switch(dir)
    {
    case LEFT:
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2-robSize/2+offset, pos.y()*FieldElement::size+FieldElement::size/2));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2-robSize/2+offset));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2+robSize/2-offset));
        break;
    case DOWN:
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2+robSize/2+offset));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2+robSize/2-offset, pos.y()*FieldElement::size+FieldElement::size/2));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2-robSize/2+offset, pos.y()*FieldElement::size+FieldElement::size/2));
        break;
    case UP:
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2-robSize/2+offset));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2+robSize/2-offset, pos.y()*FieldElement::size+FieldElement::size/2));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2-robSize/2+offset, pos.y()*FieldElement::size+FieldElement::size/2));
        break;
    case RIGHT:
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2+robSize/2+offset, pos.y()*FieldElement::size+FieldElement::size/2));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2-robSize/2+offset));
        trig.append(QPoint(pos.x()*FieldElement::size+FieldElement::size/2, pos.y()*FieldElement::size+FieldElement::size/2+robSize/2-offset));
        break;
    }
    arrow.addPolygon(trig);
    p->fillPath(arrow, QBrush(QColor(255, 0, 0)));
}
