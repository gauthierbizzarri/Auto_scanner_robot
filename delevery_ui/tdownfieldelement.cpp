#include "tdownfieldelement.h"

TDownFieldElement::TDownFieldElement(QPoint pos, FieldElement *left, FieldElement *right, FieldElement *down)
    :FieldElement(pos,
{
{Direction::LEFT, left},
{Direction::RIGHT, right},
{Direction::DOWN, down}
})
{

}

void TDownFieldElement::paint(QPainter *p)
{
    //draw the top
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    //draw the tail
    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size+FieldElement::size/2;
    width = FieldElement::thickness;
    height = FieldElement::size/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
