#include "leftrightpathmaker.h"

#include <QJsonObject>
#include <QJsonArray>
LeftRightPathMaker::LeftRightPathMaker(Direction init)
{
    this->init=init;
}

QJsonObject LeftRightPathMaker::create(QList<FieldElement *> res)
{
    if(res.count()<= 0)
    {
        return QJsonObject();
    }
    QJsonObject o;
    QJsonArray data;
    Direction dir = init;
    FieldElement *cur = res.at(0);
    int index = 0;
    for(int i = 1; i<res.count(); i++)
    {
        QString direction = "";
        if(cur->canGoTo().count()==3)
        {
            if(cur->goTo(UP) == res.at(i) && dir == RIGHT)
            {
                direction = "L";
                dir = UP;
            }
            else if(cur->goTo(UP) == res.at(i) && dir == UP && cur->canGoTo().contains(LEFT))
            {
                direction = "R";
                dir = UP;
            }
            if(cur->goTo(UP) == res.at(i) && dir == LEFT)
            {
                direction = "R";
                dir = UP;
            }
            else if(cur->goTo(UP) == res.at(i) && dir == UP && cur->canGoTo().contains(RIGHT))
            {
                direction = "L";
                dir = UP;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == RIGHT)
            {
                direction = "R";
                dir = DOWN;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == DOWN && cur->canGoTo().contains(RIGHT))
            {
                direction = "L";
                dir = DOWN;
            }
            if(cur->goTo(DOWN) == res.at(i) && dir == LEFT)
            {
                direction = "L";
                dir = DOWN;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == DOWN && cur->canGoTo().contains(LEFT))
            {
                direction = "R";
                dir = DOWN;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == UP)
            {
                direction = "L";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == LEFT && cur->canGoTo().contains(UP))
            {
                direction = "L";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == DOWN)
            {
                direction = "R";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == LEFT && cur->canGoTo().contains(DOWN))
            {
                direction = "R";
                dir = LEFT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == UP)
            {
                direction = "R";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == RIGHT && cur->canGoTo().contains(UP))
            {
                direction = "R";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == DOWN)
            {
                direction = "L";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == RIGHT && cur->canGoTo().contains(DOWN))
            {
                direction = "L";
                dir = RIGHT;
            }
        }
        else if(cur->canGoTo().count()==2)
        {
            FieldElement* element = cur;
            if(element != nullptr)
            {
                if(element->canGoTo().at(0) == UP && dir == DOWN)
                {
                    dir = element->canGoTo().at(1);
                }
                else if(element->canGoTo().at(0) == DOWN && dir == UP)
                {
                    dir = element->canGoTo().at(1);
                }
                else if(element->canGoTo().at(0) == LEFT && dir == RIGHT)
                {
                    dir = element->canGoTo().at(1);
                }
                else if(element->canGoTo().at(0) == RIGHT && dir == LEFT)
                {
                    dir = element->canGoTo().at(1);
                }
                else
                {
                    dir = element->canGoTo().at(0);
                }
            }
        }
        if(direction != "")
        {
            QJsonObject step;
            step.insert("id", index++);
            step.insert("direction", direction);
            data.append(step);
        }
        cur = res.at(i);
    }
    o.insert("data", data);
    o.insert("size", data.count());
    return o;
}
