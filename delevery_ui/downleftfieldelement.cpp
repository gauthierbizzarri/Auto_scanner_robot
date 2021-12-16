#include "downleftfieldelement.h"

DownLeftFieldElement::DownLeftFieldElement(QPoint pos, FieldElement *down, FieldElement *left)
    :FieldElement(pos,
{
{Direction::LEFT, left},
{Direction::DOWN, down}
})
{

}

void DownLeftFieldElement::paint(QPainter *p)
{
    //paint the left side
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size/2;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    //paint the down side
    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    width = FieldElement::thickness;
    height = FieldElement::size/2+FieldElement::thickness/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
