#ifndef STRAIGHTLEFTRIGHTFIELDELEMENT_H
#define STRAIGHTLEFTRIGHTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The StraightLeftRightFieldElement class
 * Field element representing a straight horizontal line
 */
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
