#ifndef TURNUPLEFTFIELDELEMENT_H
#define TURNUPLEFTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The TurnUpLeftFieldElement class
 * Class representing a smooth turn from up to left seen as a straight line
 */
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
