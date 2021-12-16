#include "FieldElementTracker.h"
#include "downleftfieldelement.h"
#include "downrightfieldelement.h"
#include "fieldmodel.h"
#include "jsonpathmaker.h"
#include "straightleftrightfieldelement.h"
#include "straightupdownfieldelement.h"
#include "tdownfieldelement.h"
#include "tleftfieldelement.h"
#include "trightfieldelement.h"
#include "tupfieldelement.h"
#include "turndownleftfieldelement.h"
#include "turndownrightfieldelement.h"
#include "turnupleftfieldelement.h"
#include "turnuprightfieldelement.h"
#include "upleftfieldelement.h"
#include "uprightfieldelement.h"

#include <QPainterPath>
#include <QJsonObject>
#include <QJsonArray>

#include <math.h>

FieldModel::FieldModel()
{
    addElement((new TurnDownRightFieldElement(QPoint(1, 0)))->setAllowedDirection({RIGHT}));
    addElement((new TDownFieldElement(QPoint(2, 0)))->setAllowedDirection({RIGHT}));
    addElement((new TDownFieldElement(QPoint(3, 0)))->setAllowedDirection({RIGHT}));
    addLoading((new TDownFieldElement(QPoint(4, 0)))->setAllowedDirection({RIGHT}), 4);
    addElement((new StraightLeftRightFieldElement(QPoint(5, 0)))->setAllowedDirection({RIGHT}));
    addElement((new TurnDownLeftFieldElement(QPoint(6, 0)))->setAllowedDirection({DOWN}));
    addElement((new TurnDownRightFieldElement(QPoint(0, 1)))->setAllowedDirection({RIGHT}));
    addLoading((new TUpFieldElement(QPoint(1, 1)))->setAllowedDirection({UP, RIGHT}), 1);
    addLoading((new TUpFieldElement(QPoint(2, 1)))->setAllowedDirection({UP, RIGHT}), 2);
    addLoading((new TUpFieldElement(QPoint(3, 1)))->setAllowedDirection({UP, RIGHT}), 3);
    addElement((new TurnUpLeftFieldElement(QPoint(4, 1)))->setAllowedDirection({UP}));
    addElement((new StraightUpDownFieldElement(QPoint(6, 1)))->setAllowedDirection({DOWN}));
    addElement((new TRightFieldElement(QPoint(0, 2)))->setAllowedDirection({UP}));
    addElement((new StraightLeftRightFieldElement(QPoint(1, 2)))->setAllowedDirection({LEFT}));
    addElement((new StraightLeftRightFieldElement(QPoint(2, 2)))->setAllowedDirection({LEFT}));
    addElement((new StraightLeftRightFieldElement(QPoint(3, 2)))->setAllowedDirection({LEFT}));
    addElement((new StraightLeftRightFieldElement(QPoint(4, 2)))->setAllowedDirection({LEFT}));
    addElement((new StraightLeftRightFieldElement(QPoint(5, 2)))->setAllowedDirection({LEFT}));
    addAnalyse((new TLeftFieldElement(QPoint(6, 2)))->setAllowedDirection({LEFT, DOWN}));
    addElement((new TurnUpRightFieldElement(QPoint(0, 3)))->setAllowedDirection({UP}));
    addDeposit((new TDownFieldElement(QPoint(1, 3)))->setAllowedDirection({LEFT}), 1);
    addDeposit((new TDownFieldElement(QPoint(2, 3)))->setAllowedDirection({LEFT}), 2);
    addDeposit((new TDownFieldElement(QPoint(3, 3)))->setAllowedDirection({LEFT}), 3);
    addElement((new TurnDownLeftFieldElement(QPoint(4, 3)))->setAllowedDirection({LEFT}));
    addElement((new StraightUpDownFieldElement(QPoint(6, 3)))->setAllowedDirection({DOWN}));
    addElement((new TurnUpRightFieldElement(QPoint(1, 4)))->setAllowedDirection({UP}));
    addElement((new TUpFieldElement(QPoint(2, 4)))->setAllowedDirection({UP, LEFT}));
    addElement((new TUpFieldElement(QPoint(3, 4)))->setAllowedDirection({UP, LEFT}));
    addDeposit((new TUpFieldElement(QPoint(4, 4)))->setAllowedDirection({UP, LEFT}), 4);
    addElement((new StraightLeftRightFieldElement(QPoint(5, 4)))->setAllowedDirection({LEFT}));
    addElement((new TurnUpLeftFieldElement(QPoint(6, 4)))->setAllowedDirection({LEFT}));

    srand(time(0));
    robots.insert("ROBOT3", new Robot(deposits.value(3)->getPosition(), QColor(rand()%150+100, rand()%150+100, rand()%150+100), UP));
    lastLoading = -1;
}

void FieldModel::draw(QPainter *p, FieldElement *e)
{
    e->paint(p);
}

void FieldModel::drawAll(QPainter *p)
{
    Q_FOREACH(FieldElement* e, elements)
    {
        if(loadings.values().contains(e))
        {
            p->setPen(QPen(QColor(0, 0, 0), 1));
            p->drawRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size,FieldElement::size);
            p->fillRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size, FieldElement::size, QBrush(QColor(166,219,248,125)));
            p->drawText(e->getPosition().x()*FieldElement::size+5, e->getPosition().y()*FieldElement::size+FieldElement::size-5, QString::number(loadings.key(e)));
        }
        if(deposits.values().contains(e))
        {
            p->setPen(QPen(QColor(0, 0, 0), 1));
            p->drawRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size,FieldElement::size);
            p->fillRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size, FieldElement::size, QBrush(QColor(246,178,107,125)));
            p->drawText(e->getPosition().x()*FieldElement::size+5, e->getPosition().y()*FieldElement::size+FieldElement::size-5, QString::number(deposits.key(e)));
        }
        if(analyse.contains(e))
        {
            p->setPen(QPen(QColor(0, 0, 0), 1));
            p->drawRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size,FieldElement::size);
            p->fillRect(e->getPosition().x()*FieldElement::size, e->getPosition().y()*FieldElement::size, FieldElement::size, FieldElement::size, QBrush(QColor(204,238,226,200)));
            p->drawText(e->getPosition().x()*FieldElement::size+5, e->getPosition().y()*FieldElement::size+FieldElement::size-5, QString::number(analyse.indexOf(e)+1));
        }
        e->paint(p);
    }
    Q_FOREACH(QString robot, orderFollowers.keys())
    {
        orderFollowers.value(robot)->draw(p);
    }
    Q_FOREACH(Robot* robot, robots.values())
    {
        robot->draw(p);
    }
}

void FieldModel::addElement(FieldElement *e)
{
    if(elements.contains(e))
    {
        return;
    }
    QPoint p = e->getPosition();
    FieldElement* element = at(p);
    if(element != nullptr)
    {
        elements.removeOne(element);
        if(deposits.values().contains(element))
        {
            deposits.remove(deposits.key(element));
        }
        if(loadings.values().contains(element))
        {
            loadings.remove(loadings.key(element));
        }
    }
    QPoint up = p;
    up.setY(up.y()-1);
    QPoint down = p;
    down.setY(down.y()+1);
    QPoint left = p;
    left.setX(left.x()-1);
    QPoint right = p;
    right.setX(right.x()+1);
    FieldElement* upE = at(up);
    FieldElement* downE = at(down);
    FieldElement* leftE = at(left);
    FieldElement* rightE = at(right);
    Q_FOREACH(Direction d, e->canGoTo())
    {
        switch(d)
        {
        case UP:
            if(upE != nullptr && upE->canGoTo().contains(Direction::DOWN))
            {
                e->addToward(Direction::UP, upE);
                upE->addToward(Direction::DOWN, e);
            }
            break;
        case DOWN:
            if(downE != nullptr && downE->canGoTo().contains(Direction::UP))
            {
                e->addToward(Direction::DOWN, downE);
                downE->addToward(Direction::UP, e);
            }
            break;
        case LEFT:
            if(leftE != nullptr && leftE->canGoTo().contains(Direction::RIGHT))
            {
                e->addToward(Direction::LEFT, leftE);
                leftE->addToward(Direction::RIGHT, e);
            }
            break;
        case RIGHT:
            if(rightE != nullptr && rightE->canGoTo().contains(Direction::LEFT))
            {
                e->addToward(Direction::RIGHT, rightE);
                rightE->addToward(Direction::LEFT, e);
            }
            break;
        }
    }
    elements.append(e);
    emit changed();
}

void FieldModel::addDeposit(FieldElement *e, int index)
{
    if(!deposits.values().contains(e))
        deposits.insert(index, e);
    if(loadings.values().contains(e))
    {
        loadings.remove(loadings.key(e));
    }
    if(analyse.contains(e)){
        analyse.removeOne(e);
    }
    addElement(e);
}

void FieldModel::addLoading(FieldElement *e, int index)
{
    if(!loadings.values().contains(e))
        loadings.insert(index, e);
    if(deposits.values().contains(e))
    {
        deposits.remove(deposits.key(e));
    }
    if(analyse.contains(e)){
        analyse.removeOne(e);
    }
    addElement(e);
}

FieldElement *FieldModel::getLoading(int index)
{
    if(!loadings.contains(index))
        return nullptr;
    return loadings.value(index);
}

const QMap<int, FieldElement *> FieldModel::getLoadings()
{
    return loadings;
}

FieldElement *FieldModel::getDeposit(int index)
{
    if(!deposits.contains(index))
        return nullptr;
    return deposits.value(index);
}

const QMap<int, FieldElement *> FieldModel::getDeposits()
{
    return deposits;
}

int FieldModel::depositIndex(FieldElement *e)
{
    if(!deposits.values().contains(e))
        return -1;
    return deposits.key(e);
}

FieldElement *FieldModel::getAnalyse(int index)
{
    if(analyse.count()<= index || index < 0)
        return nullptr;
    return analyse.at(index);
}

void FieldModel::addAnalyse(FieldElement *e)
{
    if(!analyse.contains(e))
        analyse.append(e);
    if(loadings.values().contains(e))
    {
        loadings.remove(loadings.key(e));
    }
    if(deposits.values().contains(e))
    {
        deposits.remove(deposits.key(e));
    }
    addElement(e);
}

FieldElement *FieldModel::at(QPoint pos)
{
    Q_FOREACH(FieldElement* e, elements)
    {
        if(e->getPosition() == pos)
        {
            return e;
        }
    }
    return nullptr;
}

bool FieldModel::moveRobot(QString robotId, QPoint pos)
{
    if(at(pos) == nullptr)
    {
        return false;
    }
    if(robots.contains(robotId))
    {
        Robot *robot = robots.value(robotId);
        robot->moveAt(pos);
        emit changed();
        return true;
    }
    return false;
}

float distanceBetween(QPoint p1, QPoint p2)
{
    return (sqrt(pow(p1.x()-p2.x(), 2)+pow(p1.y()-p2.y(), 2)));
}

FieldElementTracker* lowerF(QList<FieldElementTracker*> list)
{
    FieldElementTracker *t = list.at(0);
    for(int i = 1; i<list.count(); i++)
    {
        FieldElementTracker *next = list.at(i);
        if(next->getValue() < t->getValue())
        {
            t = next;
        }
    }
    return t;
}

FieldElementTracker* fromElement(FieldElement* element, QList<FieldElementTracker*> list)
{
    Q_FOREACH(FieldElementTracker* t, list)
    {
        if(t->getElement() == element)
        {
            return t;
        }
    }
    return nullptr;
}

QList<FieldElement*> FieldModel::getPath(Direction init, FieldElement* from, FieldElement* to)
{
    QList<FieldElementTracker*> open{new FieldElementTracker(from, 0+distanceBetween(from->getPosition(), to->getPosition()))};
    QList<FieldElementTracker*> closed;
    while(!open.isEmpty())
    {
        FieldElementTracker *select = lowerF(open);
        open.removeOne(select);
        closed.append(select);
        if(select->getElement()->getPosition() == to->getPosition())
        {
            QList<FieldElement*> res;
            while(select != nullptr)
            {
                res.push_front(select->getElement());
                select=select->getParent();
            }
            return res;
        }
        Q_FOREACH(Direction d, select->getElement()->alowedToGoTo())
        {
            FieldElement* e = select->getElement()->goTo(d);
            if(fromElement(e, closed) == nullptr && fromElement(e, open) == nullptr)
            {

                FieldElementTracker* element = new FieldElementTracker(e, 0);
                element->setDistance(select->getDistance()+1);
                element->setValue(element->getDistance()+distanceBetween(element->getElement()->getPosition(), to->getPosition()));
                element->setParent(select);
                open.append(element);
            }
            else
            {
                FieldElementTracker* t = fromElement(e, closed);
                if(t == nullptr)
                {
                    t = fromElement(e, open);
                }
                if(t->getDistance()>select->getDistance()+1)
                {
                    t->setDistance(select->getDistance()+1);
                    t->setValue(t->getDistance()+distanceBetween(t->getElement()->getPosition(), to->getPosition()));
                    t->setParent(select);
                    if(closed.contains(t))
                    {
                        closed.removeOne(t);
                        open.append(t);
                    }
                }
            }
        }
    }
    return QList<FieldElement*>();
}

void FieldModel::setLastLoading(int v)
{
    if(loadings.keys().contains(v))
    {
        lastLoading = v;
    }
}

int FieldModel::getLastLoading()
{
    return lastLoading;
}

void FieldModel::ColorFound(QString color)
{
    if(loadings.keys().contains(lastLoading))
    {
        colorsFound.insert(lastLoading, color);
    }
}

void FieldModel::ColorFound(int loading, QString color)
{
    if(loadings.keys().contains(loading))
    {
        colorsFound.insert(loading, color);
    }
}

QMap<int, QString> FieldModel::getColorsFound()
{
    return colorsFound;
}

void FieldModel::setRobotAvailable(QString robot)
{
    if(orderFollowers.contains(robot))
    {
        delete orderFollowers.take(robot);
    }
    if(robots.contains(robot))
    {
        if(robots.value(robot)->getStatus() == RobotStatus::TOLOAD)
        {
            robots.value(robot)->setStatus(RobotStatus::TOANALYSE);
        }
        else if(robots.value(robot)->getStatus() == RobotStatus::RELOAD)
        {
            robots.value(robot)->setStatus(RobotStatus::TOANALYSE);
        }
        else if (robots.value(robot)->getStatus() == RobotStatus::TODEPOSIT)
        {
            robots.value(robot)->setReadyForOrder(true);
            robots.value(robot)->setStatus(RobotStatus::TOLOAD);
            lastLoading = -1;
        }
        else if(robots.value(robot)->getStatus() == RobotStatus::TOANALYSE)
        {
            if(robots.value(robot)->getCarriedColor() == robots.value(robot)->getColorToLookFor())
            {
                robots.value(robot)->setStatus(RobotStatus::TODEPOSIT);
                QList<FieldElement*> path = getPath(robots.value(robot)->pointing(), at(robots.value(robot)->getPosition()), at(robots.value(robot)->startedOn()));
                if(path.count() > 0)
                {
                    emit newPath(robot, path);
                }
            }
            else
            {
                robots.value(robot)->setStatus(RobotStatus::BACKTOLOADING);
                QList<FieldElement*> path = getPath(robots.value(robot)->pointing(), at(robots.value(robot)->getPosition()), loadings.value(lastLoading));
                if(path.count() > 0)
                {
                    emit newPath(robot, path);
                }
            }
        }
        else if(robots.value(robot)->getStatus() == RobotStatus::BACKTOLOADING)
        {
            lastLoading = (lastLoading+1)%(loadings.count()+1);
            if(lastLoading == 0)
            {
                lastLoading = 1;
            }
            robots.value(robot)->setStatus(RobotStatus::RELOAD);
        }
    }
}

QMap<QString, Robot *> FieldModel::getRobots()
{
    return robots;
}

bool FieldModel::followSteps(QString robotid, OrderFollower *follower)
{
    if(robots.contains(robotid))
    {
        if(orderFollowers.contains(robotid))
        {
            return false;
        }
        orderFollowers.insert(robotid, follower);
        connect(follower, SIGNAL(orderEnd(QString)), this, SLOT(setRobotAvailable(QString)));
        emit changed();
        return true;
    }
    return false;
}

OrderFollower *FieldModel::follower(QString robotid)
{
    if(!orderFollowers.contains(robotid))
        return nullptr;
    return orderFollowers.value(robotid);
}
