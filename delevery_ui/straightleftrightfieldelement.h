#ifndef STRAIGHTLEFTRIGHTFIELDELEMENT_H
#define STRAIGHTLEFTRIGHTFIELDELEMENT_H

#include "fieldelement.h"



class StraightLeftRightFieldElement : public FieldElement
{
public:
    StraightLeftRightFieldElement(QPoint pos, FieldElement* left =nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // STRAIGHTLEFTRIGHTFIELDELEMENT_H
