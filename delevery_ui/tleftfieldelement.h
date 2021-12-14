#ifndef TLEFTFIELDELEMENT_H
#define TLEFTFIELDELEMENT_H

#include "fieldelement.h"



class TLeftFieldElement : public FieldElement
{
public:
    TLeftFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* down = nullptr, FieldElement* left = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // TLEFTFIELDELEMENT_H
