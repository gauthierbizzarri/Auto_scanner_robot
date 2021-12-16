#ifndef TUPFIELDELEMENT_H
#define TUPFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The TUpFieldElement class
 * Class representing an upside down T
 */
class TUpFieldElement : public FieldElement
{
public:
    TUpFieldElement(QPoint pos, FieldElement* left = nullptr, FieldElement* up = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // TUPFIELDELEMENT_H
