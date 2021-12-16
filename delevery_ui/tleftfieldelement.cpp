#include "tleftfieldelement.h"

TLeftFieldElement::TLeftFieldElement(QPoint pos, FieldElement *up, FieldElement *down, FieldElement *left)
    :FieldElement(pos,
{
{Direction::UP, up},
{Direction::LEFT, left},
{Direction::DOWN, down}
})
{

}

void TLeftFieldElement::paint(QPainter *p)
{
    //draw the left sided top
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size/2;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    //draw the left sided tail
    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size;
    width = FieldElement::thickness;
    height = FieldElement::size;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
