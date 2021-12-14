#ifndef TDOWNFIELDELEMENT_H
#define TDOWNFIELDELEMENT_H

#include "fieldelement.h"



class TDownFieldElement : public FieldElement
{
public:
    TDownFieldElement(QPoint pos, FieldElement* left = nullptr, FieldElement* right = nullptr, FieldElement* down = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // TDOWNFIELDELEMENT_H
