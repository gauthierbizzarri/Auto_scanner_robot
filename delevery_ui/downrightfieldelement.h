#ifndef DOWNRIGHTFIELDELEMENT_H
#define DOWNRIGHTFIELDELEMENT_H

#include "fieldelement.h"



class DownRightFieldElement : public FieldElement
{
public:
    DownRightFieldElement(QPoint pos, FieldElement* down = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // DOWNRIGHTFIELDELEMENT_H
