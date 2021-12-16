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
public:
    static int size; //in px
    static int thickness;
    FieldElement(QPoint pos, QMap<Direction, FieldElement*> nexts){
        position = pos;
        this->nexts = nexts;
        directionFilter = nexts.keys();
    };
    virtual void paint(QPainter *p) = 0;
    virtual QString letter(Direction from, Direction to){
        if(!nexts.keys().contains(to) || !directionFilter.contains(to))
        {
            return "";
        }
        if((from == UP && to == DOWN) || (from == LEFT && to == RIGHT) || (from == DOWN && to == UP) || (from == RIGHT && to == LEFT))
        {
            return "LL";
        }
        else if((from == UP && to == LEFT) || (from == LEFT && to == DOWN) || (from == DOWN && to == RIGHT) || (from == RIGHT && to == UP))
        {
            return "L";
        }
        else if(from == to)
        {
            return "F";
        }
        else{
            return "R";
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
    virtual QList<Direction> alowedToGoTo()
    {
        QList<Direction> res;
        Q_FOREACH(Direction d, nexts.keys())
        {
            if(directionFilter.contains(d))
                res.append(d);
        }
        return res;
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
