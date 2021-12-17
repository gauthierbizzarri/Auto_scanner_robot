#include "straightupdownfieldelement.h"

StraightUpDownFieldElement::StraightUpDownFieldElement(QPoint pos, FieldElement *up, FieldElement *down)
    :FieldElement(pos,
{
{Direction::DOWN, down},
{Direction::UP, up}
})
{

}

void StraightUpDownFieldElement::paint(QPainter *p)
{
    //draw the line
    int x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int y = position.y()*FieldElement::size;
    int width = FieldElement::thickness;
    int height = FieldElement::size;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}

QString StraightUpDownFieldElement::letter(Direction from, Direction to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    return "";//not an intersection
}
