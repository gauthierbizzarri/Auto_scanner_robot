#ifndef FIELDELEMENT_H
#define FIELDELEMENT_H

#include <QPainter>
#include <direction.h>
#include <QMap>

class FieldElement
{
protected:
    QMap<Direction, FieldElement*> nexts;
    QList<Direction> directionFilter;
    QPoint position;
    static int size; //in px
    static int thickness;
public:
    FieldElement(QPoint pos, QMap<Direction, FieldElement*> nexts){
        position = pos;
        this->nexts = nexts;
        directionFilter = nexts.keys();
    };
    virtual void paint(QPainter *p) = 0;
    virtual QString letter(Direction from, Direction to){
        if(!nexts.keys().contains(from) || !nexts.keys().contains(to) || !directionFilter.contains(to) || from == to)
        {
            return "";
        }
        if((from == UP && to == DOWN) || (from == LEFT && to == RIGHT) || (from == DOWN && to == UP) || (from == RIGHT && to == LEFT))
        {
            return "F";
        }
        else if((from == UP && to == LEFT) || (from == LEFT && to == DOWN) || (from == DOWN && to == RIGHT) || (from == RIGHT && to == UP))
        {
            return "R";
        }
        else{
            return "L";
        }
    };

    virtual FieldElement* goTo(Direction d){
        if(!nexts.contains(d) && directionFilter.contains(d))
        {
            return nullptr;
        }
        return nexts.value(d);
    };
    virtual void addToward(Direction d, FieldElement* f)
    {
        if(directionFilter.contains(d) && nexts.keys().contains(d))
        {
            nexts.insert(d, f);
        }
    };
    virtual QPoint getPosition()
    {
        return position;
    };
    virtual FieldElement* setAllowedDirection(QList<Direction> dirs)
    {
        directionFilter = dirs;
        return this;
    };
    virtual QList<Direction> canGoTo(){
        QList<Direction> res;
        Q_FOREACH(Direction d, nexts.keys())
        {
            res.append(d);
        }
        return res;
    };
};

#endif // FIELDELEMENT_H
