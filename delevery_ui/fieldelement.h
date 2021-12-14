#ifndef FIELDELEMENT_H
#define FIELDELEMENT_H

#include <QPainter>
#include <direction.h>
#include <QMap>

class FieldElement
{
protected:
    QMap<Direction, FieldElement*> nexts;
    QPoint position;
    static int size; //in px
    static int thickness;
public:
    FieldElement(QPoint pos, QMap<Direction, FieldElement*> nexts){
        position = pos;
        this->nexts = nexts;
    };
    virtual void paint(QPainter *p) = 0;

    virtual FieldElement* goTo(Direction d){
        if(!nexts.contains(d))
        {
            return nullptr;
        }
        return nexts.value(d);
    };
    virtual void addToward(Direction d, FieldElement* f)
    {
        nexts.insert(d, f);
    };
    virtual QPoint getPosition()
    {
        return position;
    };
    virtual QList<Direction> canGoTo(){
        return nexts.keys();
    };
};

#endif // FIELDELEMENT_H
