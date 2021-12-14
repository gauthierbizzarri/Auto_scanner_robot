#ifndef UPLEFTFIELDELEMENT_H
#define UPLEFTFIELDELEMENT_H

#include "fieldelement.h"



class UpLeftFieldElement : public FieldElement
{
public:
    UpLeftFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* left = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // UPLEFTFIELDELEMENT_H
