#include "trightfieldelement.h"

TRightFieldElement::TRightFieldElement(QPoint pos, FieldElement *up, FieldElement *down, FieldElement *right)
    :FieldElement(pos,
{
{Direction::UP, up},
{Direction::RIGHT, right},
{Direction::DOWN, down}
})
{

}

void TRightFieldElement::paint(QPainter *p)
{
    int x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int y = position.y()*FieldElement::size;
    int width = FieldElement::thickness;
    int height = FieldElement::size;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    x = position.x()*FieldElement::size+FieldElement::size/2;
    y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    width = FieldElement::size/2;
    height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
