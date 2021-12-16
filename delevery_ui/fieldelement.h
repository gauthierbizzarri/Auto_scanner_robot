#ifndef FIELDELEMENT_H
#define FIELDELEMENT_H

#include <QPainter>
#include <direction.h>
#include <QMap>

/**
 * @brief The FieldElement class
 * Base class of a field element, used to unifiate all element across the field
 */
class FieldElement
{
protected:
    QMap<Direction, FieldElement*> nexts;
    QList<Direction> directionFilter;
    QPoint position;
public:
    //cell size
    static int size; //in px
    //line thickness
    static int thickness;
    FieldElement(QPoint pos, QMap<Direction, FieldElement*> nexts){
        position = pos;
        this->nexts = nexts;
        directionFilter = nexts.keys();
    };
    /**
     * @brief paint
     * Custom element's paint method
     * @param p
     */
    virtual void paint(QPainter *p) = 0;

    /**
     * @brief letter
     * Aquire the letter represented by a direction's input and output in the element
     * @param from
     * @param to
     * @return
     */
    virtual QString letter(Direction from, Direction to){
        if(!nexts.keys().contains(to) || !directionFilter.contains(to)) //if its not possible to access the element from from direction or if to direction is locked
        {
            return "";
        }
        if((from == UP && to == DOWN) || (from == LEFT && to == RIGHT) || (from == DOWN && to == UP) || (from == RIGHT && to == LEFT)) //if exiting the way you entered
        {
            return "LL";
        }
        else if((from == UP && to == LEFT) || (from == LEFT && to == DOWN) || (from == DOWN && to == RIGHT) || (from == RIGHT && to == UP)) //if exiting to the left side you entered
        {
            return "L";
        }
        else if(from == to) //if exiting the same way you entered
        {
            return "F";
        }
        else{
            return "R";
        }
    };

    /**
     * @brief goTo
     * Gets the next element attached on direction d, or null if impossible
     * @param d
     * @return
     */
    virtual FieldElement* goTo(Direction d){
        if(!nexts.contains(d) && directionFilter.contains(d))
        {
            return nullptr;
        }
        return nexts.value(d);
    };

    /**
     * @brief addToward
     * Adds an element to the attached elements of this one on the d direction
     * @param d
     * @param f
     */
    virtual void addToward(Direction d, FieldElement* f)
    {
        if(directionFilter.contains(d) && nexts.keys().contains(d))
        {
            nexts.insert(d, f);
        }
    };

    /**
     * @brief getPosition
     * @return the element's position
     */
    virtual QPoint getPosition()
    {
        return position;
    };

    /**
     * @brief setAllowedDirection
     * Set allowed directions, locking some ones
     * @param dirs
     * @return
     */
    virtual FieldElement* setAllowedDirection(QList<Direction> dirs)
    {
        directionFilter = dirs;
        return this;
    };

    /**
     * @brief alowedToGoTo
     * @return The directions you can effectively go to from this element
     */
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

    /**
     * @brief canGoTo
     * @return All the direction you would have been allowed to take (even locked ones) from this element
     */
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
