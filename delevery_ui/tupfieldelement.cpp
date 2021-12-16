#include "tupfieldelement.h"

TUpFieldElement::TUpFieldElement(QPoint pos, FieldElement *left, FieldElement *up, FieldElement *right) : FieldElement(pos,
{
{Direction::LEFT, left},
{Direction::RIGHT, right},
{Direction::UP, up}
})
{

}

void TUpFieldElement::paint(QPainter *p)
{
    //draw the upside down top
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    //draw the upside down tail
    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size;
    width = FieldElement::thickness;
    height = FieldElement::size/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
