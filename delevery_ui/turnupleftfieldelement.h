#ifndef TURNUPLEFTFIELDELEMENT_H
#define TURNUPLEFTFIELDELEMENT_H

#include "fieldelement.h"



class TurnUpLeftFieldElement : public FieldElement
{
public:
    TurnUpLeftFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* left= nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QString letter(Direction from, Direction to);
};

#endif // TURNUPLEFTFIELDELEMENT_H
