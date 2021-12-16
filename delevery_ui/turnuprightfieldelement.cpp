#include "turnuprightfieldelement.h"

TurnUpRightFieldElement::TurnUpRightFieldElement(QPoint pos, FieldElement *up, FieldElement *right)
    :FieldElement(pos,
{
{Direction::RIGHT, right},
{Direction::UP, up}
})
{

}

void TurnUpRightFieldElement::paint(QPainter *p)
{
    //draw arc
    QPen pen(QColor(0, 0, 0), FieldElement::thickness);
    p->setPen(pen);
    p->drawArc(position.x()*FieldElement::size+FieldElement::size/2,
               position.y()*FieldElement::size-FieldElement::size/2+FieldElement::thickness,
               FieldElement::size-FieldElement::thickness,
               FieldElement::size - FieldElement::thickness,
               2850, 1500);
}

QString TurnUpRightFieldElement::letter(Direction from, Direction to)
{
    return "";
}
