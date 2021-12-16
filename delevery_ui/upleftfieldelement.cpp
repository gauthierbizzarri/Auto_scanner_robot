#include "upleftfieldelement.h"

UpLeftFieldElement::UpLeftFieldElement(QPoint pos, FieldElement *up, FieldElement *left)
    :FieldElement(pos,
{
{Direction::UP, up},
{Direction::LEFT, left}
})
{

}

void UpLeftFieldElement::paint(QPainter *p)
{
    //draw left part
    int x = position.x()*FieldElement::size;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size/2;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    //draw up part
    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size;
    width = FieldElement::thickness;
    height = FieldElement::size/2+FieldElement::thickness/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
