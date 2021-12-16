#ifndef TURNUPRIGHTFIELDELEMENT_H
#define TURNUPRIGHTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The TurnUpRightFieldElement class
 * Class representing a smooth turn from up to right seen as a straight line
 */
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
