#ifndef DOWNLEFTFIELDELEMENT_H
#define DOWNLEFTFIELDELEMENT_H

#include "fieldelement.h"


/**
 * @brief The DownLeftFieldElement class
 * Field element representing a path where you can go only down or left
 */
class DownLeftFieldElement : public FieldElement
{
public:
    DownLeftFieldElement(QPoint pos, FieldElement* bottom = nullptr, FieldElement* left = nullptr);

    // FieldElement interface
public:
    void paint(QPainter *p);
};

#endif // DOWNLEFTFIELDELEMENT_H
