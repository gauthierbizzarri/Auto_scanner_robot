#ifndef DOWNLEFTFIELDELEMENT_H
#define DOWNLEFTFIELDELEMENT_H

#include "fieldelement.h"



class DownLeftFieldElement : public FieldElement
{
public:
    DownLeftFieldElement(QPoint pos, FieldElement* bottom = nullptr, FieldElement* left = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
    QChar letter(Direction dir);
};

#endif // DOWNLEFTFIELDELEMENT_H
