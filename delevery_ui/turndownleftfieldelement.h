#ifndef TURNDOWNLEFTFIELDELEMENT_H
#define TURNDOWNLEFTFIELDELEMENT_H

#include "fieldelement.h"



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
