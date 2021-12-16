#include "objectpathmaker.h"

ObjectPathMaker::ObjectPathMaker(Direction dir)
{
    init = dir;
}

QList<FieldElement *> ObjectPathMaker::create(QList<FieldElement *> res)
{
    /*
     * Pretty much the same as the json version, but with objects
     * */
    QList<FieldElement *> data;
    Direction dir = init;
    FieldElement *cur = res.at(0);
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
            data.append(cur);
        }
        cur = res.at(i);
    }
    return data;
}
