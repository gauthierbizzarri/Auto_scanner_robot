#ifndef UPRIGHTFIELDELEMENT_H
#define UPRIGHTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The UpRightFieldElement class
 * Class representing a path on wich you can only go up and right
 */
class UpRightFieldElement : public FieldElement
{
public:
    UpRightFieldElement(QPoint pos, FieldElement* up = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // UPRIGHTFIELDELEMENT_H
