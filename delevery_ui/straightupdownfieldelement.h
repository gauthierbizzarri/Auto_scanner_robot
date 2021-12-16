#ifndef STRAIGHTUPDOWNFIELDELEMENT_H
#define STRAIGHTUPDOWNFIELDELEMENT_H

#include "fieldelement.h"



class StraightUpDownFieldElement : public FieldElement
{
public:
    StraightUpDownFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* down = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // STRAIGHTUPDOWNFIELDELEMENT_H
