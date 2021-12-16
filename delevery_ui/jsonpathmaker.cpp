#include "jsonpathmaker.h"
#include "direction.h"

#include <QJsonObject>
#include <QJsonArray>

JsonPathMaker::JsonPathMaker(Direction init)
{
    this->init=init;
}

QJsonObject JsonPathMaker::create(QList<FieldElement *> res)
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
        if(cur->goTo(UP) == res.at(i))
        {
            direction = cur->letter(dir, UP);
            dir = UP;
        }
        else if(cur->goTo(DOWN) == res.at(i))
        {
            direction = cur->letter(dir, DOWN);
            dir = DOWN;
        }
        if(cur->goTo(LEFT) == res.at(i))
        {
            direction = cur->letter(dir, LEFT);
            dir = LEFT;
        }
        if(cur->goTo(RIGHT) == res.at(i))
        {
            direction = cur->letter(dir, RIGHT);
            dir = RIGHT;
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
