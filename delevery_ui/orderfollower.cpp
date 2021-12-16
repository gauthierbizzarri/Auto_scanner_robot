#include "orderfollower.h"
void OrderFollower::manageDirectionInBetween(int from, int to)
{
    for(int i = from; i<=to; i++)
    {
        if(robot->pointing() == LEFT && passBy.at(i)->alowedToGoTo().contains(UP))
        {
            robot->setDirection(UP);
        }
        if(robot->pointing() == LEFT && passBy.at(i)->alowedToGoTo().contains(DOWN))
        {
            robot->setDirection(DOWN);
        }
        if(robot->pointing() == RIGHT && passBy.at(i)->alowedToGoTo().contains(DOWN))
        {
            robot->setDirection(DOWN);
        }
        if(robot->pointing() == RIGHT && passBy.at(i)->alowedToGoTo().contains(UP))
        {
            robot->setDirection(UP);
        }
        if(robot->pointing() == DOWN && passBy.at(i)->alowedToGoTo().contains(LEFT))
        {
            robot->setDirection(LEFT);
        }
        if(robot->pointing() == DOWN && passBy.at(i)->alowedToGoTo().contains(RIGHT))
        {
            robot->setDirection(RIGHT);
        }
        if(robot->pointing() == UP && passBy.at(i)->alowedToGoTo().contains(LEFT))
        {
            robot->setDirection(LEFT);
        }
        if(robot->pointing() == UP && passBy.at(i)->alowedToGoTo().contains(RIGHT))
        {
            robot->setDirection(RIGHT);
        }
    }
}

OrderFollower::OrderFollower(QString robotid, Robot *robot, QString path, QList<FieldElement *> steps, QList<FieldElement*> passBy)
{
    this->robotid = robotid;
    this->steps=steps;
    this->robot=robot;
    this->passBy = passBy;
    lastIndex = -1;
    this->path=path;
}

bool OrderFollower::toStep(int step)
{
    if(step == lastIndex+1)
    {
        if(path.at(step) == "L")
        {
            switch(robot->pointing())
            {
            case UP:
                robot->setDirection(LEFT);
                break;
            case DOWN:
                robot->setDirection(RIGHT);
                break;
            case LEFT:
                robot->setDirection(DOWN);
                break;
            case RIGHT:
                robot->setDirection(UP);
            }
        }
        else if(path.at(step) == "R")
        {
            switch(robot->pointing())
            {
            case UP:
                robot->setDirection(RIGHT);
                break;
            case DOWN:
                robot->setDirection(LEFT);
                break;
            case LEFT:
                robot->setDirection(UP);
                break;
            case RIGHT:
                robot->setDirection(DOWN);
            }
        }
        if(step+1<steps.count())
        {
            robot->moveAt(steps.at(step+1)->getPosition());
            manageDirectionInBetween(passBy.indexOf(steps.at(step))+1, passBy.indexOf(steps.at(step+1))-1);
        }
        else
        {
            manageDirectionInBetween(passBy.indexOf(steps.at(step))+1, passBy.count()-2);
            robot->moveAt(passBy.last()->getPosition());
            emit orderEnd(robotid);
            return false;
        }
        lastIndex = step;
    }
    return true;
}

int OrderFollower::lastStep()
{
    return steps.count()-1;
}

void OrderFollower::draw(QPainter *p)
{
    int thicknessRatio = 3;
    if(passBy.count()>1 && lastIndex < steps.count()-1)
    {
        p->setPen(QPen(QBrush(robot->getColor()), FieldElement::thickness/thicknessRatio));
        FieldElement* first = passBy.at(passBy.indexOf(steps.at(lastIndex+1)));
        for(int i = passBy.indexOf(steps.at(lastIndex+1))+1; i < passBy.count(); i++)
        {
            p->drawLine(first->getPosition().x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/thicknessRatio/2,
                        first->getPosition().y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/thicknessRatio/2,
                        passBy.at(i)->getPosition().x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/thicknessRatio/2,
                        passBy.at(i)->getPosition().y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/thicknessRatio/2);
            first = passBy.at(i);
        }
    }
}
