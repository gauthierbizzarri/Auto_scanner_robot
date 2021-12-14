#ifndef TRIGHTFIELDELEMENT_H
#define TRIGHTFIELDELEMENT_H

#include "fieldelement.h"



class TRightFieldElement : public FieldElement
{
public:
    TRightFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* down = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // TRIGHTFIELDELEMENT_H
