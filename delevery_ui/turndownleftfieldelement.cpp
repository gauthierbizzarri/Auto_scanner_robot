#include "turndownleftfieldelement.h"

TurnDownLeftFieldElement::TurnDownLeftFieldElement(QPoint pos, FieldElement *down, FieldElement *left)
    :FieldElement(pos,
{
{Direction::DOWN, down},
{Direction::LEFT, left}
})
{

}

void TurnDownLeftFieldElement::paint(QPainter *p)
{
    //draw the arc
    QPen pen(QColor(0, 0, 0), FieldElement::thickness);
    p->setPen(pen);
    p->drawArc(position.x()*FieldElement::size-FieldElement::size/2+FieldElement::thickness,
               position.y()*FieldElement::size+FieldElement::size/2,
               FieldElement::size-FieldElement::thickness,
               FieldElement::size - FieldElement::thickness,
               1450, -1450);
}

QString TurnDownLeftFieldElement::letter(Direction from, Direction to)
{
    return "";
}
