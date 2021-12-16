#ifndef TURNDOWNLEFTFIELDELEMENT_H
#define TURNDOWNLEFTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The TurnDownLeftFieldElement class
 * Class representing a smooth turn from down to left seen as a straight line
 */
class TurnDownLeftFieldElement : public FieldElement
{
public:
    TurnDownLeftFieldElement(QPoint pos, FieldElement* down = nullptr, FieldElement* left = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // TURNDOWNLEFTFIELDELEMENT_H
