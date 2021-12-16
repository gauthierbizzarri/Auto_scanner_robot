#ifndef TURNUPRIGHTFIELDELEMENT_H
#define TURNUPRIGHTFIELDELEMENT_H

#include "fieldelement.h"



class TurnUpRightFieldElement : public FieldElement
{
public:
    TurnUpRightFieldElement(QPoint pos, FieldElement* up=nullptr, FieldElement* right =nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // TURNUPRIGHTFIELDELEMENT_H
