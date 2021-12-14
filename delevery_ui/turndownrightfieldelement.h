#ifndef TURNDOWNRIGHTFIELDELEMENT_H
#define TURNDOWNRIGHTFIELDELEMENT_H

#include "fieldelement.h"



class TurnDownRightFieldElement : public FieldElement
{
public:
    TurnDownRightFieldElement(QPoint pos, FieldElement* down = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // TURNDOWNRIGHTFIELDELEMENT_H
