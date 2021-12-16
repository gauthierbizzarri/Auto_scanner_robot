#ifndef DOWNRIGHTFIELDELEMENT_H
#define DOWNRIGHTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The DownRightFieldElement class
 * Field element used to represent a path on which you can only go down and right
 */
class DownRightFieldElement : public FieldElement
{
public:
    DownRightFieldElement(QPoint pos, FieldElement* down = nullptr, FieldElement* right = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // DOWNRIGHTFIELDELEMENT_H
