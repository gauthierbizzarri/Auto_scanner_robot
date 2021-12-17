#include "turndownrightfieldelement.h"

TurnDownRightFieldElement::TurnDownRightFieldElement(QPoint pos, FieldElement *down, FieldElement *right)
    :FieldElement(pos,
{
{Direction::DOWN, down},
{Direction::RIGHT, right}
})
{

}

void TurnDownRightFieldElement::paint(QPainter *p)
{
    //draw arc
    QPen pen(QColor(0, 0, 0), FieldElement::thickness);
    p->setPen(pen);
    p->drawArc(position.x()*FieldElement::size+FieldElement::size/2,
               position.y()*FieldElement::size+FieldElement::size/2,
               FieldElement::size-FieldElement::thickness,
               FieldElement::size - FieldElement::thickness,
               1450, 1500);
}

QString TurnDownRightFieldElement::letter(Direction from, Direction to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    return "";
}
