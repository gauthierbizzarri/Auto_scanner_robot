#include "turnupleftfieldelement.h"

TurnUpLeftFieldElement::TurnUpLeftFieldElement(QPoint pos, FieldElement *up, FieldElement *left)
    :FieldElement(pos,
{
{Direction::LEFT, left},
{Direction::UP, up}
})
{

}

void TurnUpLeftFieldElement::paint(QPainter *p)
{
    //draw arc
    QPen pen(QColor(0, 0, 0), FieldElement::thickness);
    p->setPen(pen);
    p->drawArc(position.x()*FieldElement::size-FieldElement::size/2+FieldElement::thickness,
               position.y()*FieldElement::size-FieldElement::size/2+FieldElement::thickness,
               FieldElement::size-FieldElement::thickness,
               FieldElement::size - FieldElement::thickness,
               0, -1450);
}

QString TurnUpLeftFieldElement::letter(Direction from, Direction to)
{
    return "";
}
