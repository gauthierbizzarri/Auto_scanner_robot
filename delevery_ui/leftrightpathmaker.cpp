#include "leftrightpathmaker.h"

#include <QJsonObject>
#include <QJsonArray>
LeftRightPathMaker::LeftRightPathMaker(Direction init)
{
    this->init=init;
}

QJsonObject LeftRightPathMaker::create(QList<FieldElement *> res)
{
    /*
     * To enderstand this methos, you must notice that
     * the direction dir represents the direction you entered the element from,
     * and the "goTo" direction is the one you will exit by
     *
     * the purpose of this is to always detect intersections with both left and right laser sensors
     *
     * this method does not work if you have elements with more than 3 possible directions
    */
    if(res.count()<= 0)
    {
        return QJsonObject();
    }
    //TODO : SIMPLIFY !!!
    QJsonObject o;
    QJsonArray data;
    Direction dir = init;
    FieldElement *cur = res.at(0);
    int index = 0;
    for(int i = 1; i<res.count(); i++)
    {
        QString direction = "";
        if(cur->canGoTo().count()==3)//for 3 path elements
        {
            if(cur->goTo(UP) == res.at(i) && dir == RIGHT)//if goint up heading right
            {
                direction = "L";
                dir = UP;
            }
            else if(cur->goTo(UP) == res.at(i) && dir == UP && cur->canGoTo().contains(LEFT))//if going up heading up, with a left path available
            {
                direction = "R";
                dir = UP;
            }
            if(cur->goTo(UP) == res.at(i) && dir == LEFT)//if going up heading left
            {
                direction = "R";
                dir = UP;
            }
            else if(cur->goTo(UP) == res.at(i) && dir == UP && cur->canGoTo().contains(RIGHT))//if going up heading up, with an available path to the right
            {
                direction = "L";
                dir = UP;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == RIGHT)//if going down heading right
            {
                direction = "R";
                dir = DOWN;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == DOWN && cur->canGoTo().contains(RIGHT))//if going down heading down, with an available path to the right
            {
                direction = "L";
                dir = DOWN;
            }
            if(cur->goTo(DOWN) == res.at(i) && dir == LEFT)//if going down heading left
            {
                direction = "L";
                dir = DOWN;
            }
            else if(cur->goTo(DOWN) == res.at(i) && dir == DOWN && cur->canGoTo().contains(LEFT))//if going down heading down, with an available path to the left
            {
                direction = "R";
                dir = DOWN;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == UP)//if going left heading up
            {
                direction = "L";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == LEFT && cur->canGoTo().contains(UP))//if going left heading left, with an available path to the up
            {
                direction = "L";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == DOWN)//if going left heading down
            {
                direction = "R";
                dir = LEFT;
            }
            else if(cur->goTo(LEFT) == res.at(i) && dir == LEFT && cur->canGoTo().contains(DOWN))//if going left heading left, with an available path to the down
            {
                direction = "R";
                dir = LEFT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == UP)//if going right heading up
            {
                direction = "R";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == RIGHT && cur->canGoTo().contains(UP))//if going right heading right, with an available path to the up
            {
                direction = "R";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == DOWN)//if going right heading down
            {
                direction = "L";
                dir = RIGHT;
            }
            else if(cur->goTo(RIGHT) == res.at(i) && dir == RIGHT && cur->canGoTo().contains(DOWN))//if going right heading right, with an availablepath to the down
            {
                direction = "L";
                dir = RIGHT;
            }
        }
        else if(cur->canGoTo().count()==2)//for 2 paths elements
        {
            FieldElement* element = cur;
            if(element != nullptr)
            {
                //gtet the one we didn't arrived in
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
