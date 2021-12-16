#include "straightleftrightfieldelement.h"

StraightLeftRightFieldElement::StraightLeftRightFieldElement(QPoint pos, FieldElement *left, FieldElement *right)
    :FieldElement(pos,
{
{Direction::LEFT, left},
{Direction::RIGHT, right}
})
{

}

void StraightLeftRightFieldElement::paint(QPainter *p)
{
    //draw the line
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}


QString StraightLeftRightFieldElement::letter(Direction from, Direction to)
{
    return "";//no letter info for this element (not an intersection)
}
